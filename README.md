# Wi-Fi Provisioning using BLE in ESP-IDF

Explaination of the implementation of Wi-Fi provisioning using BLE (Bluetooth Low Energy) in ESP-IDF. Wi-Fi provisioning enables devices to receive Wi-Fi credentials via a BLE-enabled mobile app.


## Introduction

Wi-Fi provisioning via BLE allows users to configure their ESP32 devices with Wi-Fi credentials through a BLE-enabled app. ESP-IDF simplifies this process with a provisioning manager module. **Important:** The provisioning service name must begin with the prefix `PROV_` for compatibility with mobile apps.

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

