| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 | Linux |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | ----- |

# UART with Non-Volatile Memory Access

This Program reads the incomming data from UART and save in Non-Volatile memory with following methods : 
1. FAT System : It can write the data in chunks which means we can append the data.
2. NVS System : all the data has to be written at once we can not append the data in chunks

To switch between `FAT System` and `NVS System` change the value of ``USE_NVS`` from the `main.cpp`. 

## File Structure
``
├── CMakeLists.txt

├── main                          # Holds all the source code

│   ├── CMakeLists.txt            

│   ├── include

│   │   ├── FAT_Storage.h         # FAT System Header file

│   │   └── NVS_Storage.h         # NVS System Header file

│   ├── main.cpp                  # Holds the main app

│   └── src                       

│       ├── FAT_Storage.cpp       # FAT System Source file

│       └── NVS_Storage.cpp       # NVS System Source file

├── partitions.csv                # Partition details csv

├── pytest_hello_world.py

├── README.md

├── Scripts

│   └── serialtest.py             # Python script to send the serial data from PC

├── sdkconfig                     # ESP MCU Configuration

├── sdkconfig.ci

└── sdkconfig.old

``


## How to use

clone the repo.

source the `idf.py` in the terminal.

select your target device, supported device in the avobe table.

Build the repo with `idf.py build`.

Flash the firmware to the controller by `idf.py flash`.

monitor the serial on 2400 budrate by `idf.py monitor -b 2400`.

Run the python script from `Scripts\Serialtest.py`.

Observe the result in the serial monitor.

## API Reference

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

## Technical support and feedback

Please use the following feedback channels:

* For technical queries, go to the [esp32.com](https://esp32.com/) forum
* For a feature request or bug report, create a [GitHub issue](https://github.com/espressif/esp-idf/issues)

