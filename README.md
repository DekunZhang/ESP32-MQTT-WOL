# ESP32-MQTT-WOL

Please mannually add a `confidential.h` and write the following macros.
```c
#ifndef __CONFIDENTIAL_H__
#define __CONFIDENTIAL_H__

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define MQTT_HOST ""
#define CLIENT_ID ""
#define MQTT_USER ""
#define MQTT_PASS ""

#define MAC_ADDRESS ""

#endif
```
