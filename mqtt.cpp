#include <PubSubClient.h>
#include "connect_wifi.h"
#include "commons.h"
#include "wake_device.h"

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long last_msg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    char chars[length + 1];
    memcpy(chars, payload, length);
    chars[length] = '\0';
    Serial.println(chars);
    String message(chars);
    if (message.equals("WakeDevice"))
        wakeMyPC();
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        if (!is_wifi_connected())
        {
            connect_wifi();
        }

        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(CLIENT_ID, MQTT_USER, MQTT_PASS))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "Device connected");
            // ... and resubscribe
            client.subscribe("inTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup_mqtt()
{
    if (!is_wifi_connected())
    {
        connect_wifi();
    }

    client.setServer(MQTT_HOST, 1883);
    client.setCallback(callback);
}

void mqtt_loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - last_msg > 30000)
    {
        last_msg = now;
        snprintf(msg, MSG_BUFFER_SIZE, "Waiting for message...");
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("outTopic", msg);
    }
}