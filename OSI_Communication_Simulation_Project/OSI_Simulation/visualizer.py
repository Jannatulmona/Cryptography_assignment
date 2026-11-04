
import socket
import subprocess
import threading
import time

HOST = "127.0.0.1"
MONITOR_PORT = 9090

stop_listener = threading.Event()

progress = {
    "ENCAP": 0,
    "DECAP": 0
}


# Receive real-time events from C client and server
def show_event(message):

    parts = message.split("|", 4)

    if len(parts) != 5:
        return

    role, action, layer, name, detail = parts

    if action == "START":
        print(f"\n{detail}")

    elif action == "ENCAP":

        print(f"\nSENDER -> Layer {layer}: {name}")
        print(f"Data: {detail}")

        progress["ENCAP"] += 1
        count = progress["ENCAP"]

        if count % 2 == 0 or count == 7:
            print(f"Encapsulation progress: {count}/7 layers")

    elif action == "SOCKET":

        print(f"\n[TCP SOCKET] {role}: {detail}")

    elif action == "DECAP":

        print(f"\nRECEIVER <- Layer {layer}: {name}")
        print(f"Data: {detail}")

        progress["DECAP"] += 1
        count = progress["DECAP"]

        if count % 2 == 0 or count == 7:
            print(f"Decapsulation progress: {count}/7 layers")

    elif action == "RESULT":

        print(f"\n[SUCCESS] {detail}")

    elif action == "ERROR":

        print(f"\n[ERROR] {role}: {detail}")


# Python UDP listener
def listen_for_events(monitor):

    while not stop_listener.is_set():

        try:
            data, address = monitor.recvfrom(4096)

            message = data.decode(
                "utf-8",
                errors="replace"
            )

            show_event(message)

        except socket.timeout:
            continue

        except OSError:
            break


# OSI 7-layer explanatory visualization
def show_zigzag():

    print("\n")
    print("=" * 60)
    print("       OSI 7-LAYER SIMULATION STARTED")
    print("=" * 60)

    print("\nOriginal Data: HELLO")

    print("\nStarting Encapsulation...\n")

    sender_layers = [
        (7, "Application", "Preparing application data..."),
        (6, "Presentation", "Formatting data..."),
        (5, "Session", "Establishing session..."),
        (4, "Transport", "Adding TCP header..."),
        (3, "Network", "Adding IP header..."),
        (2, "Data Link", "Creating Ethernet frame..."),
        (1, "Physical", "Transmitting bits...")
    ]

    for number, name, action in sender_layers:

        print(f"Layer {number}: {name}")
        print(action)

        if number in (6, 4, 2, 1):
            completed = 8 - number
            print(
                f"Encapsulation progress: {completed}/7 layers"
            )

        print("-" * 40)

    print("\nEncapsulation complete!")

    print("\nSending data through REAL TCP SOCKET...")
    print("CLIENT  -------- TCP --------> SERVER")

    print("\nStarting Decapsulation...\n")

    receiver_layers = [
        (1, "Physical", "Bits received"),
        (2, "Data Link", "Frame processed"),
        (3, "Network", "IP header removed"),
        (4, "Transport", "TCP header removed"),
        (5, "Session", "Session processed"),
        (6, "Presentation", "Data decoded"),
        (7, "Application", "Final data received")
    ]

    for number, name, action in receiver_layers:

        print(f"Layer {number}: {name} -> {action}")

        if number in (2, 4, 6, 7):
            print(
                f"Decapsulation progress: {number}/7 layers"
            )

        print("-" * 40)

    print("\nFinal Data: HELLO")

    print("\nTRANSMISSION SUCCESSFUL!")

    print("=" * 60)


# Main program
def main():

    print("=== OSI SIMULATION STARTING ===")

    monitor = socket.socket(
        socket.AF_INET,
        socket.SOCK_DGRAM
    )

    try:
        monitor.bind((HOST, MONITOR_PORT))

    except OSError as error:

        print("Monitoring port error:", error)
        monitor.close()
        return

    monitor.settimeout(0.2)

    listener = threading.Thread(
        target=listen_for_events,
        args=(monitor,),
        daemon=True
    )

    listener.start()

    server = None

    try:

        print("Starting C server...")

        server = subprocess.Popen(
            ["server.exe"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )

        time.sleep(1)

        if server.poll() is not None:

            print("Server could not start.")
            print("Check server.exe and server.c")

            return

        print("Starting C client...\n")

        result = subprocess.run(
            ["client.exe"],
            capture_output=True,
            text=True
        )

        # Allow UDP events to arrive
        time.sleep(0.5)

        if result.returncode != 0:

            print("Client execution failed.")

            if result.stdout:
                print(result.stdout)

            if result.stderr:
                print(result.stderr)

            return

        print("\nReal TCP socket communication completed.")

        # Display requested OSI visualization
        show_zigzag()

        print("\n=== SIMULATION FINISHED ===")

    except FileNotFoundError as error:

        print("File not found:", error)
        print("Check server.exe and client.exe.")

    finally:

        stop_listener.set()

        monitor.close()

        listener.join(timeout=1)

        if server is not None and server.poll() is None:

            server.terminate()

            try:
                server.wait(timeout=2)

            except subprocess.TimeoutExpired:
                server.kill()
                server.wait()


if __name__ == "__main__":
    main()
