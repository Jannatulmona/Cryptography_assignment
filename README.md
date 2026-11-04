# 🌐 OSI 7-Layer Network Communication Simulation

<p align="center">

  **A C-Based Client-Server Networking Simulation with Python Visualization**

  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Language-Python-yellow?style=for-the-badge&logo=python" />
  <img src="https://img.shields.io/badge/Protocol-TCP%20%7C%20UDP-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows" />

</p>

---

## 📌 Project Overview

The **OSI 7-Layer Network Communication Simulation** is an educational networking project that demonstrates how data travels from a sender to a receiver through the seven layers of the OSI (Open Systems Interconnection) model.

The project uses **C-based client and server applications** to perform simulated seven-layer encapsulation and decapsulation through real TCP socket communication.

A **Python-based visualization application** monitors communication events and displays the layer-by-layer data flow, including encapsulation and decapsulation progress after every two OSI layers.

The project aims to make fundamental networking concepts easier to understand through practical socket programming and visual representation.

## 🎯 Project Objectives

- Understand the functionality of all seven OSI layers.
- Implement client-server communication using C and TCP sockets.
- Demonstrate the encapsulation and decapsulation processes.
- Visualize sender and receiver operations using Python.
- Display progress after every two OSI layers.
- Understand the relationship between the OSI model and real-world network communication.

## 🏗️ System Architecture

The project consists of three main components:

| Component | Responsibility |
|---|---|
| C Client | Performs simulated encapsulation and sends data |
| C Server | Receives data, performs decapsulation and returns the message |
| Python Visualizer | Monitors C application events and displays the simulation |

### Communication Flow

```text
              SENDER
           C CLIENT
               |
               v
      +-------------------+
      |  OSI 7-Layer      |
      |  Encapsulation    |
      +-------------------+
               |
               v
       Simulated Packet
               |
               v
      +-------------------+
      |   REAL TCP SOCKET |
      +-------------------+
               |
               v
      +-------------------+
      |     C SERVER      |
      +-------------------+
               |
               v
      +-------------------+
      |  OSI 7-Layer      |
      |  Decapsulation    |
      +-------------------+
               |
               v
       Original Message
               |
               v
        TCP Response
               |
               v
             CLIENT

       PYTHON VISUALIZER
       (UDP Event Monitoring)
               |
               v
       Layer-by-Layer Display
```

## 🔄 Understanding the OSI 7 Layers

The simulation demonstrates the following seven layers:

| Layer | Name | Simulated Operation |
|:---:|---|---|
| 7 | Application | Preparing application data |
| 6 | Presentation | Formatting data |
| 5 | Session | Managing communication session |
| 4 | Transport | Adding a simulated TCP header |
| 3 | Network | Adding a simulated IP header |
| 2 | Data Link | Creating a simulated Ethernet frame |
| 1 | Physical | Representing bit transmission |

### 📤 Encapsulation (Sender Side)

The client starts with an original message:

```text
HELLO
```

It then adds simulated headers from Layer 7 down to Layer 1.

**Encapsulation Example:**

```text
Layer 7 → [L7]HELLO
Layer 6 → [L6][L7]HELLO
Layer 5 → [L5][L6][L7]HELLO
Layer 4 → [L4][L5][L6][L7]HELLO
Layer 3 → [L3][L4][L5][L6][L7]HELLO
Layer 2 → [L2][L3][L4][L5][L6][L7]HELLO
Layer 1 → [L1][L2][L3][L4][L5][L6][L7]HELLO
```

After completing encapsulation, the client transmits the packet to the server using a real TCP socket connection.

### 📥 Decapsulation (Receiver Side)

The server receives the packet and removes the simulated headers from Layer 1 up to Layer 7.

```text
Layer 1 → [L2][L3][L4][L5][L6][L7]HELLO
Layer 2 → [L3][L4][L5][L6][L7]HELLO
Layer 3 → [L4][L5][L6][L7]HELLO
Layer 4 → [L5][L6][L7]HELLO
Layer 5 → [L6][L7]HELLO
Layer 6 → [L7]HELLO
Layer 7 → HELLO
```

Finally, the server recovers the original message and sends it back to the client.

## ✨ Key Features

- **Seven-Layer Simulation:** Demonstrates all seven OSI layers.
- **Encapsulation:** Adds simulated layer headers at the sender side.
- **Decapsulation:** Removes simulated headers at the receiver side.
- **Real TCP Communication:** Connects the C client and server using TCP sockets.
- **Python Visualization:** Monitors events from C applications using UDP.
- **Layer Progress Tracking:** Displays progress after every two layers.
- **Message Recovery:** Recovers and returns the original message.
- **Event Monitoring:** Displays sender, receiver and socket communication events.

## 🛠️ Technologies & Tools

| Technology | Usage |
|---|---|
| C Programming | Client and server applications |
| Python 3 | Visualization and event monitoring |
| TCP Socket | Client-server communication |
| UDP Socket | C-to-Python event notifications |
| Winsock2 | Windows network programming |
| GCC / MinGW | C compilation |
| Visual Studio Code | Development environment |

## 📂 Project Structure

```text
OSI_Simulation/
│
├── client.c              # C-based client application
├── server.c              # C-based server application
├── visualizer.py         # Python visualization application
│
├── client.exe            # Compiled client executable
├── server.exe            # Compiled server executable
│
└── README.md             # Project documentation
```

## ⚙️ Installation & Setup

### Prerequisites

Make sure the following tools are installed:

- Windows 10/11
- GCC Compiler (MinGW)
- Python 3.x
- Visual Studio Code (recommended)

No external Python packages are required.

### Step 1: Clone the Repository

```bash
git clone YOUR_REPOSITORY_URL
```

```bash
cd OSI_Simulation
```

Replace `YOUR_REPOSITORY_URL` with your actual GitHub repository URL.

### Step 2: Compile the Server

```bash
gcc server.c -o server.exe -lws2_32
```

### Step 3: Compile the Client

```bash
gcc client.c -o client.exe -lws2_32
```

### Step 4: Run the Simulation

```bash
python visualizer.py
```

The Python application automatically starts the C server and client, monitors their communication events and displays the simulation.

**Note:** Run only `visualizer.py`. It manages the execution of both C applications.

## 🖥️ Sample Output

### 1. Encapsulation Progress

```text
SENDER -> Layer 7: Application
Encapsulated data: [L7]HELLO

SENDER -> Layer 6: Presentation
Encapsulated data: [L6][L7]HELLO

Encapsulation progress: 2/7 layers

SENDER -> Layer 5: Session
Encapsulated data: [L5][L6][L7]HELLO

SENDER -> Layer 4: Transport
Encapsulated data: [L4][L5][L6][L7]HELLO

Encapsulation progress: 4/7 layers
```

### 2. TCP Socket Communication

```text
[TCP SOCKET] CLIENT: Sending packet to server

[TCP SOCKET] SERVER: Packet received
```

### 3. Decapsulation Progress

```text
RECEIVER <- Layer 1: Physical

RECEIVER <- Layer 2: Data Link

Decapsulation progress: 2/7 layers

RECEIVER <- Layer 3: Network

RECEIVER <- Layer 4: Transport

Decapsulation progress: 4/7 layers
```

### 4. Successful Message Transmission

```text
[SUCCESS] Reply sent to client

[SUCCESS] Server replied: HELLO
```

## 📊 Implementation Status

| Task | Status |
|---|:---:|
| C Client Implementation | ✅ |
| C Server Implementation | ✅ |
| TCP Socket Communication | ✅ |
| Seven-Layer Encapsulation | ✅ |
| Seven-Layer Decapsulation | ✅ |
| Original Message Recovery | ✅ |
| Python UDP Event Monitoring | ✅ |
| Layer-by-Layer Event Display | ✅ |
| Progress After Every Two Layers | ✅ |
| Explanatory OSI Visualization | ✅ |

## 🐧 Relation to Linux/Ubuntu Networking

The project uses the OSI model as a conceptual reference to explain how network data moves through different communication layers.

The visualization is inspired by the layered networking architecture used in Linux/Ubuntu systems, where application data passes through socket interfaces and networking protocols before reaching the network interface.

The current implementation runs on Windows using Winsock2 and MinGW.

## ⚠️ Implementation Notes & Limitations

- The `[L1]` to `[L7]` headers are educational simulation markers, not actual protocol headers.
- TCP is used for real communication between the C client and server.
- UDP is used separately for event notifications from C applications to Python.
- The Python program combines real C-generated events with an explanatory OSI visualization.
- The implementation demonstrates OSI concepts but does not implement seven independent real-world network protocols.
- The project currently uses a short demonstration message (`HELLO`).

## 🚀 Future Improvements

Possible future extensions include:

- Dynamic zig-zag visualization synchronized with real C events.
- Graphical user interface for the OSI layers.
- Support for user-defined messages.
- Improved TCP message framing and error handling.
- Linux/Ubuntu platform support.
- Packet inspection and additional network statistics.

## 🎓 Learning Outcomes

Through this project, we explore:

- OSI networking architecture.
- Client-server communication.
- TCP and UDP socket programming.
- Data encapsulation and decapsulation.
- Network data flow.
- C and Python integration.
- Event-driven monitoring and visualization.

## 📝 Conclusion

This project demonstrates the fundamental concepts of the OSI 7-layer model by combining C-based socket programming with Python visualization.

The real TCP connection between the client and server, together with simulated encapsulation and decapsulation, provides a practical way to understand how data is transmitted and recovered in a network communication system.

---

<p align="center">

  **Developed as a Computer Networks Academic Project**

  *Learning Networking Through Practical Implementation*

</p>
