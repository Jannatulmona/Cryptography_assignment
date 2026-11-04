
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define BUFFER_SIZE 1024

void notify_python(const char *event) {
    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) return;

    struct sockaddr_in monitor;
    memset(&monitor, 0, sizeof(monitor));
    monitor.sin_family = AF_INET;
    monitor.sin_addr.s_addr = inet_addr("127.0.0.1");
    monitor.sin_port = htons(9090);

    sendto(s, event, (int)strlen(event), 0,
           (struct sockaddr *)&monitor, sizeof(monitor));
    closesocket(s);
}

const char *layer_name(int layer) {
    switch (layer) {
        case 1: return "Physical";
        case 2: return "Data Link";
        case 3: return "Network";
        case 4: return "Transport";
        case 5: return "Session";
        case 6: return "Presentation";
        case 7: return "Application";
        default: return "Unknown";
    }
}

int main(void) {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char message[] = "HELLO";
    char packet[BUFFER_SIZE];
    char next[BUFFER_SIZE];
    char response[BUFFER_SIZE] = {0};
    char event[BUFFER_SIZE + 128];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (connect(client_socket, (struct sockaddr *)&server,
                sizeof(server)) == SOCKET_ERROR) {
        notify_python("CLIENT|ERROR|0|TCP Socket|Connection failed");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    strcpy(packet, message);

    notify_python("CLIENT|START|0|Application|Original message: HELLO");

    for (int layer = 7; layer >= 1; layer--) {
        snprintf(next, sizeof(next), "[L%d]%s", layer, packet);

        if (strlen(next) >= sizeof(packet)) {
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }

        strcpy(packet, next);

        snprintf(event, sizeof(event),
                 "CLIENT|ENCAP|%d|%s|%s",
                 layer, layer_name(layer), packet);
        notify_python(event);
    }

    notify_python("CLIENT|SOCKET|0|TCP Socket|Sending packet to server");

    int total = (int)strlen(packet);
    int sent = 0;

    while (sent < total) {
        int n = send(client_socket, packet + sent,
                     total - sent, 0);

        if (n == SOCKET_ERROR || n == 0) {
            notify_python("CLIENT|ERROR|0|TCP Socket|Send failed");
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }

        sent += n;
    }

    int bytes = recv(client_socket, response,
                     BUFFER_SIZE - 1, 0);

    if (bytes > 0) {
        response[bytes] = '\0';

        snprintf(event, sizeof(event),
                 "CLIENT|RESULT|0|Application|Server replied: %s",
                 response);
        notify_python(event);
    } else {
        notify_python("CLIENT|ERROR|0|TCP Socket|No reply received");
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
