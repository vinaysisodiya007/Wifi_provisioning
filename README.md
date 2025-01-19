# Wi-Fi Provisioning using BLE 

Explaination of the implementation of Wi-Fi provisioning using BLE (Bluetooth Low Energy) in ESP-IDF. Wi-Fi provisioning enables devices to receive Wi-Fi credentials via a BLE-enabled mobile app.


## Introduction

Wi-Fi provisioning via BLE allows users to configure their ESP32 devices with Wi-Fi credentials through a BLE-enabled app. ESP-IDF simplifies this process with a provisioning manager module. **Important:** The provisioning service name must begin with the prefix `PROV_` for compatibility with mobile apps.

Wi-Fi provisioning allows devices to connect to a Wi-Fi network without needing hardcoded credentials. This project implements **Wi-Fi provisioning** using **Bluetooth Low Energy (BLE)**, making it easy for devices to be configured remotely via a mobile app or other BLE-enabled devices. This is particularly useful for IoT devices that do not have a display or user interface for direct input of network credentials.

In this setup, the **ESP32** is used to handle the provisioning process. The provisioning process is initiated via BLE, and the device listens for Wi-Fi credentials (SSID and password) sent from a mobile app. Once the credentials are received, the device connects to the Wi-Fi network and can be used for further IoT applications.

### Key Features:
- **BLE-based Provisioning**: Allows Wi-Fi credentials to be sent securely over BLE.
- **QR Code Generation**: The app scans the QR code to initiate provisioning.
- **Event Handling**: Monitors events such as successful credential reception, Wi-Fi connection, and disconnection.

### Workflow:
1. **Provisioning Initiation**: BLE provisioning is initiated when the device starts, and a QR code is displayed for scanning.
2. **Credential Transmission**: A mobile app sends the Wi-Fi credentials (SSID and password) via BLE to the device.
3. **Wi-Fi Connection**: The device connects to the Wi-Fi network using the received credentials.
4. **Event Notifications**: The system provides real-time updates for successful or failed provisioning attempts.

### Benefits:
- **Easy Setup**: Eliminates the need for manually entering Wi-Fi credentials.
- **Secure**: Ensures that Wi-Fi credentials are sent securely via BLE.
- **User-friendly**: Enables mobile app-based configuration for users.

This document details the process of Wi-Fi provisioning using BLE, providing the necessary tools and instructions to set up and use the provisioning system in Arduino IDE with ESP32.

---
## Prerequisites

Ensure the following are set up before starting:  

- **SOFTWARE** i.e installed and configured IDE (Arduino IDE,ESP IDF)
  ([Setup Guide]
  (https://docs.espressif.com/)
  (https://docs.arduino.cc/software/ide-v1/tutorials/Windows/).  
- **Hardware:** ESP32 development board.  
- **Mobile App:** Espressif's official provisioning app (available on Android/iOS).  

---

