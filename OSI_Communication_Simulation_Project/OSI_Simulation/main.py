
import subprocess
import time
import sys

def main():
    print("Starting OSI Model Simulation...")
    print("=" * 40)

    # Start the C server in a separate Windows console
    server = subprocess.Popen(
        ["server.exe"],
        creationflags=subprocess.CREATE_NEW_CONSOLE
    )

    try:
        # Give the server time to start listening
        time.sleep(2)

        print("\nStarting C client...")
        result = subprocess.run(["client.exe"])

        if result.returncode != 0:
            print("Client failed. Check the C client/server output.")
            return

        print("\nReal TCP socket communication completed.")
        print("\nStarting Python OSI visualization...")
        print("=" * 40)

        # Run your existing Python visualizer
        subprocess.run([sys.executable, "visualizer.py"])

    except FileNotFoundError:
        print("Error: server.exe, client.exe, or Python file not found.")
        print("Check that all files are in the same folder.")

    finally:
        # Stop the server if it is still running
        if server.poll() is None:
            server.terminate()
            server.wait()

    print("\nOSI Simulation completed.")

if __name__ == "__main__":
    main()
