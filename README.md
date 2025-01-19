# ESP-32---BLE-provisioning
# Wi-Fi Provisioning using BLE in ESP-IDF

Explaination of the implementation of Wi-Fi provisioning using BLE (Bluetooth Low Energy) in ESP-IDF. Wi-Fi provisioning enables devices to receive Wi-Fi credentials via a BLE-enabled mobile app.

## Table of Contents

1. Introduction  
2. Prerequisites  
3. Project Structure  
4. Implementation Steps  
   - Initialize NVS  
   - Configure Wi-Fi Provisioning Manager  
   - Start BLE Provisioning  
   - Wi-Fi Initialization  
5. Code Explanation  
6. Building and Flashing  
7. Testing Wi-Fi Provisioning  
8. Troubleshooting  

---

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

## Implementation Steps

### 1. Initialize NVS  
Initialize non-volatile storage (NVS) to store Wi-Fi credentials.

```c
esp_err_t ret = nvs_flash_init();
if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
}
```

---

### 2. Configure Wi-Fi Provisioning Manager  
Set up the provisioning manager to handle BLE communication and Wi-Fi credentials.  

Define the provisioning configuration:  

```c
wifi_prov_mgr_config_t config = {
    .scheme = wifi_prov_scheme_ble,
    .scheme_event_handler = WIFI_PROV_EVENT_HANDLER_NONE
};
```

Initialize the manager:  

```c
ESP_ERROR_CHECK(wifi_prov_mgr_init(config));
```

---

### 3. Start BLE Provisioning  
Define a unique service name starting with `PROV_`:

```c
char service_name[32] = "PROV_123456";
ESP_LOGI(TAG, "Starting provisioning with service name: %s", service_name);
ESP_ERROR_CHECK(wifi_prov_mgr_start_provisioning(WIFI_PROV_SECURITY_1, "abcd1234", NULL, service_name));
```

---

### 4. Wi-Fi Initialization  
Set Wi-Fi station mode to connect to the network.

```c
ESP_ERROR_CHECK(esp_netif_init());
ESP_ERROR_CHECK(esp_event_loop_create_default());

esp_netif_create_default_wifi_sta();
wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
ESP_ERROR_CHECK(esp_wifi_init(&cfg));
ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
ESP_ERROR_CHECK(esp_wifi_start());
```

---

## Code Explanation

Below is the complete implementation of BLE-based Wi-Fi provisioning in `main.c`:  

```c
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <wifi_provisioning/manager.h>
#include <wifi_provisioning/scheme_ble.h>

static const char *TAG = "app";
static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_EVENT = BIT0;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_PROV_EVENT) {
        switch (event_id) {
        case WIFI_PROV_START:
            ESP_LOGI(TAG, "Provisioning started");
            break;
        case WIFI_PROV_CRED_RECV:
            wifi_sta_config_t *wifi_sta_cfg = (wifi_sta_config_t *)event_data;
            ESP_LOGI(TAG, "Received Wi-Fi credentials\n\tSSID: %s\n\tPassword: %s",
                     (const char *)wifi_sta_cfg->ssid, (const char *)wifi_sta_cfg->password);
            break;
        case WIFI_PROV_CRED_FAIL:
            ESP_LOGE(TAG, "Provisioning failed! Reset and retry.");
            break;
        case WIFI_PROV_CRED_SUCCESS:
            ESP_LOGI(TAG, "Provisioning successful");
            break;
        case WIFI_PROV_END:
            wifi_prov_mgr_deinit();
            break;
        }
    } else if (event_base == WIFI_EVENT) {
        switch (event_id) {
        case WIFI_EVENT_STA_START:
            esp_wifi_connect();
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            ESP_LOGI(TAG, "Disconnected. Reconnecting...");
            esp_wifi_connect();
            break;
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "Connected with IP: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_EVENT);
    }
}

void app_main(void) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    // Initialize Wi-Fi and BLE provisioning
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_event_group = xEventGroupCreate();

    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));

    wifi_prov_mgr_config_t config = {
        .scheme = wifi_prov_scheme_ble,
        .scheme_event_handler = WIFI_PROV_EVENT_HANDLER_NONE
    };

    ESP_ERROR_CHECK(wifi_prov_mgr_init(config));

    char service_name[32] = "PROV_123456";
    ESP_LOGI(TAG, "Service name: %s", service_name);

    ESP_LOGI(TAG, "Starting provisioning");
    ESP_ERROR_CHECK(wifi_prov_mgr_start_provisioning(WIFI_PROV_SECURITY_1, "abcd1234", NULL, service_name));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}
```

---
To select the board, port, and open the serial monitor in ESP-IDF development workflow, follow these steps:

### 1. **Selecting the Board**
   - Ensure your ESP32 is connected to your computer via a USB cable.
   - If not already done, configure the target board:
     ```bash
     idf.py set-target esp32
     ```
   - This command sets ESP32 as the target for your project.

### 2. **Selecting the Port**
   - Identify the port where your ESP32 is connected. Use the following command to list all available ports:
     ```bash
     COMx            # Replace x with the port number for Windows (e.g., COM3)
     ```
   - Use this port in subsequent commands, e.g.:
     ```bash
     idf.py -p /dev/ttyUSB0 flash
     ```

### 3. **Opening the Serial Monitor**
   - After flashing, you can open the serial monitor to view logs:
     ```bash
     idf.py monitor
     ```
   - Press `Ctrl+]` to exit the monitor.

### Combined Workflow Example
```bash
idf.py set-target esp32
idf.py -p /dev/ttyUSB0 flash monitor
``` 

This will flash your code to the ESP32 and immediately open the serial monitor for debugging.


## Building and Flashing

1. Configure the project:  

```bash
idf.py set-target esp32
idf.py menuconfig
```

2. Build the project:  

```bash
idf.py build
```

3. Flash the firmware to the ESP32:  

```bash
idf.py flash
```

---
