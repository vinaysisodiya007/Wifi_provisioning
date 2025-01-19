# Wi-Fi Provisioning using BLE (Arduino & ESP-IDF)

This repository demonstrates the implementation of Wi-Fi provisioning using Bluetooth Low Energy (BLE) in both Arduino IDE and ESP-IDF for the ESP32 platform. The implementation allows easy configuration of the ESP32's Wi-Fi settings through a mobile app, providing a streamlined way of connecting the device to a network.

## Folder Structure

```
/main
    /arduino_ide
       /Code
            //arduino code file
    /ESP IDF
       /Provision
            // esp code files
```

- **`/arduino`**: Contains the Arduino IDE implementation for Wi-Fi provisioning using BLE.
- **`/esp`**: Contains the ESP-IDF implementation for Wi-Fi provisioning using BLE.

## Project Overview

The project implements Wi-Fi provisioning for ESP32 using BLE in two different development environments:
1. **Arduino IDE**: A simpler and beginner-friendly environment to handle Wi-Fi provisioning.
2. **ESP-IDF**: A more advanced and flexible development environment offering more control over hardware and performance.

Both implementations make use of BLE to allow mobile apps to send Wi-Fi credentials to the ESP32 and configure it to connect to the specified network.

## **Arduino IDE - Wi-Fi Provisioning (BLE)**

In this folder, you will find the code to perform Wi-Fi provisioning using BLE in Arduino IDE. It covers:
- Setting up BLE provisioning.
- Handling BLE events.
- Receiving Wi-Fi credentials (SSID and password) from a mobile app.
- Connecting the ESP32 to the Wi-Fi network using the received credentials.

### Requirements
- Arduino IDE (configured for ESP32).
- ESP32 board library installed in the Arduino IDE.

### Instructions
1. Open the project in Arduino IDE.
2. Select the ESP32 board from the "Tools" menu.
3. Upload the code to the ESP32 board.
4. Use a mobile app to connect and provide the Wi-Fi credentials.

## **ESP-IDF - Wi-Fi Provisioning (BLE)**

This folder contains the ESP-IDF implementation for Wi-Fi provisioning using BLE. The implementation demonstrates:
- Setting up the ESP32 as a BLE provisioning server.
- Handling provisioning events.
- Receiving Wi-Fi credentials via BLE and configuring the ESP32 to connect to the Wi-Fi network.

### Requirements
- ESP-IDF development environment.
- ESP32 board connected to your development machine.

### Instructions
1. Set up ESP-IDF on your system.
2. Open the project in ESP-IDF.
3. Configure your Wi-Fi settings.
4. Flash the code to the ESP32 board.
5. Use the mobile app to send Wi-Fi credentials to the device.

## How to Use

1. **Connect the ESP32 to your computer** and upload the code from either the Arduino IDE or ESP-IDF.
2. **Use a Wi-Fi provisioning mobile app** (like the ESP32 Provisioning App) to send Wi-Fi credentials (SSID and password) to the ESP32.
3. The ESP32 will connect to the specified Wi-Fi network using the credentials received via BLE.

## Advantages of This Approach

- **Easy Setup**: The Wi-Fi credentials can be easily provisioned without needing a direct connection to the ESP32.
- **Cross-Platform**: The implementation supports both Arduino IDE (for beginners) and ESP-IDF (for advanced users).
- **BLE-based Provisioning**: BLE makes it easy to configure ESP32 over a wireless connection, avoiding the need for cables or direct network access.
