# Wi-Fi Provisioning Using BLE in Arduino IDE

This document provides a detailed explanation of how Wi-Fi provisioning was implemented using **Bluetooth Low Energy (BLE)** on the **ESP32** microcontroller in the **Arduino IDE**. The purpose of this implementation is to allow users to provision Wi-Fi credentials to the ESP32 device over Bluetooth without the need for a physical display or wired connection.

## Task Overview

The task involved creating a **Wi-Fi provisioning system** using **Bluetooth Low Energy (BLE)** on the **ESP32**. The ESP32 was configured to act as a BLE server, enabling a smartphone or any BLE-enabled device to send Wi-Fi credentials (SSID and password) over Bluetooth. Once the credentials were received, the ESP32 automatically connected to the specified Wi-Fi network.

## Implementation Steps

### 1. Setup Arduino IDE for ESP32

To begin, the **Arduino IDE** was set up to support ESP32 development by following these steps:
- Installing **ESP32 board support** via the **Boards Manager** in the Arduino IDE.
- Selecting the **ESP32 Dev Module** as the target board from the **Tools** menu.
- Installing the necessary libraries such as **WiFi.h** for Wi-Fi connectivity and **WiFiProv.h** for BLE-based provisioning.

### 2. BLE Library Integration

The **WiFiProv** library was used to handle Wi-Fi provisioning over BLE. The integration of BLE with the ESP32 was achieved as follows:
- Configuring the ESP32 to advertise a BLE service for Wi-Fi credentials transfer.
- Setting up the BLE service and characteristics to handle provisioning requests from a client (such as a mobile app).

### 3. Wi-Fi Provisioning Implementation

Wi-Fi provisioning was done using **BLE** as the communication channel. The ESP32, upon receiving Wi-Fi credentials via BLE, connected to the specified Wi-Fi network. The following steps were involved:
- Using the **WiFiProv.beginProvision** method to initiate the BLE provisioning.
- Configuring the provisioning service with a **service name** and **POP code** (Proof of Provisioning) for secure connection.
- Generating a **QR code** that could be scanned by a mobile app to facilitate the connection.

### 4. Code Explanation
Here is the breakdown and explanation of the code in sections:
```markdown
---

### 1. **Library Inclusions**
```cpp
#include "WiFiProv.h" 
#include "WiFi.h"
```
- **WiFiProv.h**: Provides functions for Wi-Fi provisioning using BLE.
- **WiFi.h**: Handles Wi-Fi functionality, including connecting to networks and managing Wi-Fi events.

---

### 2. **Constants and Variables**
```cpp
const char *pop = "abcd1234";  // POP code for authentication
const char *service_name = "PROV_123";  // BLE service name
const char *service_key = NULL;  // Optional service key
bool reset_provisioned = true;  // Reset flag for provisioning
```
- **pop**: A code used for secure provisioning (usually a predefined password or token).
- **service_name**: The name of the BLE service used for Wi-Fi provisioning.
- **service_key**: Optional key used for BLE service authentication (set to `NULL` in this case).
- **reset_provisioned**: Flag to reset the device's previously provisioned credentials before new provisioning.

---

### 3. **Event Handler Function**
```cpp
void SysProvEvent(arduino_event_t *sys_event) {
    switch (sys_event->event_id) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.printf("\nConnected IP: %s\n", IPAddress(sys_event->event_info.got_ip.ip_info.ip.addr).toString().c_str());
            break;
        case ARDUINO_EVENT_PROV_CRED_RECV:
            Serial.printf("\nReceived Wi-Fi Credentials\n\tSSID: %s\n\tPassword: %s\n",
                          sys_event->event_info.prov_cred_recv.ssid,
                          sys_event->event_info.prov_cred_recv.password);
            break;
        case ARDUINO_EVENT_PROV_CRED_SUCCESS:
            Serial.println("\nProvisioning Successful!");
            break;
        default:
            break;
    }
}
```
- **SysProvEvent**: Handles Wi-Fi and provisioning-related events. It receives an event structure and processes different event IDs.
    - **ARDUINO_EVENT_WIFI_STA_GOT_IP**: Triggered when the device successfully connects to Wi-Fi and acquires an IP address.
    - **ARDUINO_EVENT_PROV_CRED_RECV**: Triggered when Wi-Fi credentials are received during provisioning (SSID and password).
    - **ARDUINO_EVENT_PROV_CRED_SUCCESS**: Triggered when provisioning is successful.
    - The event handler ensures that relevant information is printed to the serial monitor at each stage.

---

### 4. **Setup Function**
```cpp
void setup() {
    Serial.begin(115200);  // Initialize Serial Monitor
    WiFi.onEvent(SysProvEvent);  // Set event handler for Wi-Fi events
```
- **Serial.begin(115200)**: Initializes the serial monitor for debugging and output.
- **WiFi.onEvent(SysProvEvent)**: Registers the `SysProvEvent` function to handle Wi-Fi-related events.

---

### 5. **Starting Wi-Fi Provisioning**
```cpp
    Serial.println("Starting BLE Provisioning...");
    uint8_t uuid[16] = {0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
                        0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02};
```
- **Serial.println("Starting BLE Provisioning...")**: Prints a message indicating the start of the provisioning process.
- **uuid[16]**: A unique identifier for the BLE service, used during provisioning. This 16-byte UUID is essential for distinguishing the BLE provisioning service.

---

### 6. **BLE Provisioning Initialization**
```cpp
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name, service_key, uuid, reset_provisioned);
```
- **WiFiProv.beginProvision()**: Starts the BLE provisioning process with the specified parameters:
    - **WIFI_PROV_SCHEME_BLE**: Specifies that BLE will be used for provisioning.
    - **WIFI_PROV_SCHEME_HANDLER_FREE_BTDM**: A BLE handler to manage connections in a free BTDM (Bluetooth Device Management) mode.
    - **WIFI_PROV_SECURITY_1**: Security scheme for the provisioning process.
    - **pop**: Pre-shared provisioning code for security.
    - **service_name**: Name of the BLE service used during provisioning.
    - **service_key**: Optional key for service authentication (NULL in this case).
    - **uuid**: Unique identifier for the provisioning service.
    - **reset_provisioned**: A flag to reset previous provisioning information if `true`.

---

### 7. **QR Code for Provisioning**
```cpp
    WiFiProv.printQR(service_name, pop, "ble");  // Generate QR code for app-based provisioning
}
```
- **WiFiProv.printQR()**: Generates a QR code that can be scanned by a provisioning app to initiate the provisioning process:
    - **service_name**: Name of the BLE service for identification.
    - **pop**: Provisioning code for security.
    - **"ble"**: Indicates the provisioning method (BLE).

---

### 8. **Loop Function**
```cpp
void loop() {}
```
- **loop()**: Empty loop function. The program does not need to run any continuous logic in the loop since provisioning is handled by events.

---


#### Code Breakdown:
- **WiFiProv.beginProvision**: Initializes the BLE provisioning process with the specified settings.
- **SysProvEvent**: Handles various provisioning events, including receiving Wi-Fi credentials or the connection status.
- **WiFi.onEvent**: This is used to handle Wi-Fi events like connection, disconnection, and IP acquisition.
- **WiFiProv.printQR**: Generates a QR code that can be scanned by the mobile app for connecting to the provisioning service.

### 5. Testing

To test the Wi-Fi provisioning process, a **BLE app** (such as **nRF Connect**) was used:
- The ESP32 device was discovered, and a connection was established using the BLE app.
- The **Wi-Fi SSID** and **password** were sent via the BLE connection.
- The ESP32 successfully connected to the specified Wi-Fi network, and the results were displayed in the serial monitor.

## Challenges and Solutions

### Challenge 1: BLE Device Communication
- There were issues with BLE communication stability, and the device would disconnect unexpectedly.
  
  **Solution**: Ensured that the BLE server remained active and properly handled connections, with attention to any potential conflicts in Bluetooth settings.

### Challenge 2: Wi-Fi Connection Timeout
- The ESP32 was taking longer than expected to connect to the Wi-Fi network after receiving the credentials.
  
  **Solution**: Implemented retries and delay checks to ensure the ESP32 remained responsive during longer connection times.

### Challenge 3: Handling Multiple Connections
- Managing multiple BLE connections posed a challenge initially.

  **Solution**: Ensured proper handling of BLE client disconnections and reconnects using appropriate callbacks.

## OUTPUT

1.

<img src="https://github.com/user-attachments/assets/4441b79c-a368-48d3-828f-ef23397e8a7b" alt="Screenshot 2025-01-19 154841" width="50%">

2.
<img src="https://github.com/user-attachments/assets/789dc0e4-dd8e-475b-b47d-7dcaead3ec27" alt="IMG-20250119-WA0041" width="500">

3.
<img src="https://github.com/user-attachments/assets/53c0d96d-1178-4c54-8a3c-776207a497a9" alt="IMG-20250119-WA0040" width="500">

4.
<img src="https://github.com/user-attachments/assets/576cbf29-2597-435a-a2a2-741a4e4bb49b" alt="IMG-20250119-WA0039" width="500">

5.
<img src="https://github.com/user-attachments/assets/bec78b93-971f-428e-ad16-76eddb86ff8b" alt="IMG-20250119-WA0038" width="500">

6.
<img src="https://github.com/user-attachments/assets/940cc88b-eda8-49cd-b3b2-71695bd3bdda" alt="IMG-20250119-WA0036" width="500">

7.
<img src="https://github.com/user-attachments/assets/ff7d7eaf-d17c-43d3-9618-7c037aab83b4" alt="IMG-20250119-WA0037" width="500">

8.
<img src="https://github.com/user-attachments/assets/27e0b2fb-0999-4543-ad30-936627883f39" alt="Screenshot 2025-01-19 154857" width="500">

## FINAL RESULT VIDEO(click on the img)
[![Results VIDEO](https://img.youtube.com/vi/QT-zrRaPSUc/0.jpg)](https://youtu.be/QT-zrRaPSUc?si=0Wb2nN6YIh4JXf1G)



---

## Conclusion

This implementation successfully demonstrated how to provision Wi-Fi credentials to an **ESP32** using **Bluetooth Low Energy (BLE)**. The solution allows users to configure Wi-Fi settings without needing any physical interface, making it ideal for headless IoT devices. The system is reliable and can be extended for more advanced features like secure provisioning and additional settings.

This project provides valuable insights into working with **BLE**, **Wi-Fi**, and the **ESP32** in the **Arduino IDE**, and can be further enhanced to support additional features as needed.
```
