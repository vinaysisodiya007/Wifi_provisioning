# ESP-32---BLE-provisioning
# Wi-Fi Provisioning using BLE in ESP-IDF

Explaination of the implementation of Wi-Fi provisioning using BLE (Bluetooth Low Energy) in ESP-IDF. Wi-Fi provisioning enables devices to receive Wi-Fi credentials via a BLE-enabled mobile app.


## Introduction

Wi-Fi provisioning via BLE allows users to configure their ESP32 devices with Wi-Fi credentials through a BLE-enabled app. ESP-IDF simplifies this process with a provisioning manager module. **Important:** The provisioning service name must begin with the prefix `PROV_` for compatibility with mobile apps.

---

## Prerequisites

Ensure the following are set up before starting:  

- **ESP-IDF** installed and configured ([Setup Guide](https://docs.espressif.com/)).  
- **Hardware:** ESP32 development board.  
- **Mobile App:** Espressif's official provisioning app (available on Android/iOS).  
- Familiarity with **C programming** and the ESP-IDF framework.

---

## Project Structure

```plaintext
provisioning_project/
├── main/                          
│   ├── CMakeLists.txt             //Project Configuration
│   └── main.c                     //Main C file
├── CMakeLists.txt
└── sdkconfig                      //configuration file
```

---

