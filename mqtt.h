#ifndef __MQTT_H__
#define __MQTT_H__

void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
void setup_mqtt();
void mqtt_loop();

#endif