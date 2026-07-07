#include "WiFiManager.h"

#include <WiFi.h>

#include "config.h"
#include "DisplayManager.h"

WiFiManager WiFiMgr;

//==================================================
// Initialize WiFi
//==================================================

void WiFiManager::begin()
{
    Display.drawConnectingScreen();

    WiFi.mode(WIFI_STA);

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);

        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");

    String ip = WiFi.localIP().toString();

    Serial.print("IP: ");
    Serial.println(ip);

    Display.drawIPAddress(
        ip.c_str()
    );

    delay(1500);
}

//==================================================
// WiFi loop
//==================================================

void WiFiManager::loop()
{

}

//==================================================
// Connection state
//==================================================

bool WiFiManager::connected() const
{
    return WiFi.status() == WL_CONNECTED;
}

bool WiFiManager::isConnected() const
{
    return connected();
}