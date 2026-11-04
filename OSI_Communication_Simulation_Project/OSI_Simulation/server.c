
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
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_size = sizeof(client);
    char buffer[BUFFER_SIZE] = {0};
    char prefix[16];
    char event[BUFFER_SIZE + 128];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server,
             sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 1) == SOCKET_ERROR) {
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server waiting for client...\n");

    client_socket = accept(server_socket,
        (struct sockaddr *)&client, &client_size);

    if (client_socket == INVALID_SOCKET) {
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    int bytes = recv(client_socket, buffer,
                     BUFFER_SIZE - 1, 0);

    if (bytes <= 0) {
        notify_python("SERVER|ERROR|0|TCP Socket|No data received");
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    buffer[bytes] = '\0';

    notify_python("SERVER|SOCKET|0|TCP Socket|Packet received");
    printf("\nReceived packet: %s\n", buffer);

    for (int layer = 1; layer <= 7; layer++) {
        snprintf(prefix, sizeof(prefix), "[L%d]", layer);
        size_t prefix_len = strlen(prefix);

        if (strncmp(buffer, prefix, prefix_len) != 0) {
            snprintf(event, sizeof(event),
                     "SERVER|ERROR|0|TCP Socket|Expected %s", prefix);
            notify_python(event);

            closesocket(client_socket);
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        memmove(buffer, buffer + prefix_len,
                strlen(buffer + prefix_len) + 1);

        snprintf(event, sizeof(event),
                 "SERVER|DECAP|%d|%s|%s",
                 layer, layer_name(layer), buffer);
        notify_python(event);
    }

    printf("Original message recovered: %s\n", buffer);

    int total = (int)strlen(buffer);
    int sent = 0;

    while (sent < total) {
        int n = send(client_socket, buffer + sent,
                     total - sent, 0);

        if (n == SOCKET_ERROR || n == 0)
            break;

        sent += n;
    }

    notify_python("SERVER|RESULT|0|Application|Reply sent to client");

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
