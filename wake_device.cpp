#include <WiFiUdp.h>
#include <WakeOnLan.h>
#include "connect_wifi.h"
#include "commons.h"
#include "wake_device.h"

WiFiUDP UDP;
WakeOnLan WOL(UDP);

void wakeMyPC()
{
    // Send Wake On Lan packet with the above MAC address. Default to port 9.
    Serial.print("Waking device with MAC address: ");
    Serial.println(MAC_ADDRESS);
    WOL.sendMagicPacket(MAC_ADDRESS);
    // WOL.sendMagicPacket(MACAddress, 7); // Change the port number
}

void setup_wol()
{
    WOL.setRepeat(3, 100);
    if (!is_wifi_connected())
        connect_wifi();
    WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
}