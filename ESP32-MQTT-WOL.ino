#include "commons.h"
#include "connect_wifi.h"
#include "mqtt.h"
#include "wake_device.h"

void setup()
{
    Serial.begin(BROADCAST_RATE);
    connect_wifi();
    setup_wol();
    setup_mqtt();
}

void loop()
{
    mqtt_loop();
}