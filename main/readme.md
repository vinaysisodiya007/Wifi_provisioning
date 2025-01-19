## IMPLEMENT STEPS

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
## To select the board, port, and open the serial monitor in ESP-IDF development workflow, follow these steps:

Do it directly from the idf...

From the Top Left Section You Can directly Build , Run, Select Port,Board in ESP IDF. 

![Screenshot 2025-01-19 141709](https://github.com/user-attachments/assets/70df4785-f5e5-408c-a1f2-76097ee51cde)

### To Build Click On Hammer Icon...

![Screenshot 2025-01-19 151135](https://github.com/user-attachments/assets/cd1c9e57-c9a2-475e-bcc9-5d2e73dbad71)

### To Run Or Flash the Code to Board Click On Playback Icon...
![Screenshot 2025-01-19 151157](https://github.com/user-attachments/assets/328859e2-a45f-45ff-98c8-0d51c2b39f69)

### Ensure You Select Correct Board and Ports..
![Screenshot 2025-01-19 151240](https://github.com/user-attachments/assets/db15d6e1-2736-464f-8bf8-483d725a4ab7)

### Selecting board..
![Screenshot 2025-01-19 151224](https://github.com/user-attachments/assets/0c6a6562-ce1e-4097-8e81-fb94ec1764e7)

### Selecting Port...
![Screenshot 2025-01-19 151317](https://github.com/user-attachments/assets/033cf825-772a-4676-a42f-d1e12995712e)

Or do it via terminal...

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
