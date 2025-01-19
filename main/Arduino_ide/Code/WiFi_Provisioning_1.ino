#include "WiFiProv.h"
#include "WiFi.h"

const char *pop = "abcd1234";
const char *service_name = "PROV_123";
const char *service_key = NULL;
bool reset_provisioned = true;

void SysProvEvent(arduino_event_t *sys_event) {
    switch (sys_event->event_id) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.printf("\nConnected IP: %s\n", IPAddress(sys_event->event_info.got_ip.ip_info.ip.addr).toString().c_str());
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.println("\nDisconnected. Reconnecting...");
            break;
        case ARDUINO_EVENT_PROV_START:
            Serial.println("\nProvisioning started. Use the app to connect.");
            break;
        case ARDUINO_EVENT_PROV_CRED_RECV:
            Serial.printf("\nReceived Wi-Fi Credentials\n\tSSID: %s\n\tPassword: %s\n",
                          sys_event->event_info.prov_cred_recv.ssid,
                          sys_event->event_info.prov_cred_recv.password);
            break;
        case ARDUINO_EVENT_PROV_CRED_FAIL:
            Serial.println("\nProvisioning failed. Check Wi-Fi credentials.");
            break;
        case ARDUINO_EVENT_PROV_CRED_SUCCESS:
            Serial.println("\nProvisioning Successful!");
            break;
        case ARDUINO_EVENT_PROV_END:
            Serial.println("\nProvisioning Complete.");
            break;
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.onEvent(SysProvEvent);

    Serial.println("Starting BLE Provisioning...");
    uint8_t uuid[16] = {0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
                        0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02};
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name, service_key, uuid, reset_provisioned);
    WiFiProv.printQR(service_name, pop, "ble");
}

void loop() {}
