# UART_Task   
**ESP32 UART Performance and Data Storage Test**

This project demonstrates **UART communication between an ESP32** and a **Python host script** for measuring serial data transfer rate and optionally storing received data into **FAT** or **NVS** storage.  

The setup allows you to benchmark UART throughput and experiment with ESP32 storage and FreeRTOS-based UART handling.

---

## Repository Structure

```
UART_Task/
├── main/
│   ├── main.cpp                # ESP32 main application logic
│   ├── include/
│   │   ├── FAT_Storage.h       # FAT storage interface
│   │   └── NVS_Storage.h       # NVS storage interface
│   └── src/
│       ├── FAT_Storage.cpp     # FAT file write logic
│       └── NVS_Storage.cpp     # NVS key-value storage logic
├── Scripts/
│   └── serialtest.py           # Python script to send UART data
├── partitions.csv              # ESP32 flash partition layout
├── sdkconfig.ci                # ESP-IDF configuration file
├── CMakeLists.txt              # ESP-IDF build system configuration
└── README.md                   # Project documentation
```

---

## ESP32 Application Overview

The firmware is written using **ESP-IDF** and runs under **FreeRTOS**.  
It performs continuous UART reception, measures data throughput, and can optionally save data to **FAT** or **NVS**.

### Features
- UART initialization and data reception  
- Real-time **data rate calculation** (bps)  
- Switchable storage backends: FAT or NVS  
- Simple, extendable structure for testing serial throughput

### Configuration
In `main.cpp`:
```cpp
#define USE_NVS 0          // 0 = Use FAT, 1 = Use NVS
#define UART_NUM UART_NUM_0
#define TXD_PIN GPIO_NUM_43
#define RXD_PIN GPIO_NUM_44
#define RTS GPIO_NUM_15
#define CTS GPIO_NUM_16
#define READ_TIMEOUT_MS 1000
```

### Key Functions

#### `print_data_rate(float time_interval, uint32_t bytes_received)`
Calculates and prints the current UART data rate:
```
bits_received = bytes_received * 8
data_rate_bps = bits_received / time_interval
```

---

## Python Host Script

The Python script (`Scripts/serialtest.py`) runs on your PC and sends a data payload to the ESP32 via serial connection.


### Functionality
- Opens `/dev/ttyUSB0` at **2400 baud**.
- Waits briefly for ESP32 to initialize.
- Sends a long text message to ESP32.
- ESP32 measures and logs received speed.

You can modify:
- The **baud rate** (e.g., `115200`)
- The **payload text** or binary data

---

## System Workflow

```
┌──────────────────┐       UART TX/RX        ┌──────────────────┐
│   Python Script  │ ─────────────────────→  │      ESP32       │
│  (serialtest.py) │                         │ (main.cpp + IDF) │
└──────────────────┘                         └──────────────────┘
           │                                           │
           │                Prints bps logs            │
           └───────────────────────────────────────────┘
```

---

## How to Run

### **1 Flash ESP32**
```bash
idf.py set-target esp32s3
idf.py build
idf.py flash
idf.py monitor
```

### **2 Run Python Script**
Install dependency:
```bash
pip install pyserial
```

Run the test:
```bash
python3 Scripts/serialtest.py
```

Monitor ESP output:
```
bits_received: 8320 bR and time interval 0.567
Speed: 14676 bps
```

---

## Notes
- To use **NVS storage**, set:
  ```cpp
  #define USE_NVS 1
  ```
- UART GPIOs can be changed in `main.cpp` if needed.
- The Python script can be extended for stress testing or binary transmission.
- Works on ESP32-S3 and other ESP-IDF compatible boards.

---

## Requirements

### ESP32 Firmware
- [ESP-IDF v5+](https://github.com/espressif/esp-idf)
- USB-UART connection

### Host System
- Python 3.8+
- `pyserial` package

---

## Example Output

```
bits_received: 8320 bR and time interval 0.567
Speed: 14676 bps
```

---

---

## 👨‍💻 Author
**Pankaj Sharma**  
If you have questions, suggestions, or collaboration ideas:  
- Connect on [LinkedIn](https://www.linkedin.com/in/pankaj-k-sharma/)  
- Or open a discussion in the [Issues](../../issues) tab  
