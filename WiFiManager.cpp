#include "WiFiManager.h"

#include <WiFi.h>

#include "config.h"
#include "DisplayManager.h"

WiFiManager WiFiMgr;

void WiFiManager::begin()
{
    Display.clear();

    Display.drawHeader("--:--", false);

    auto &oled = Display.oled();

    oled.setFont(u8g2_font_helvB10_tf);

    oled.drawStr(8, 32, "Connecting");

    oled.drawStr(8, 48, "WiFi...");

    Display.update();

    WiFi.mode(WIFI_STA);

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);

        Serial.print(".");
    }

    Serial.println();

    Serial.println("WiFi Connected");

    Serial.println(WiFi.localIP());

    Display.clear();

    Display.drawHeader("--:--", true);

    oled.setFont(u8g2_font_helvB10_tf);

    oled.drawStr(8, 28, "WiFi Connected");

    oled.setFont(u8g2_font_6x12_tf);

    oled.drawUTF8(
        8,
        48,
        WiFi.localIP().toString().c_str()
    );

    Display.update();

    delay(1500);
}

void WiFiManager::loop()
{

}

bool WiFiManager::connected()
{
    return WiFi.status() == WL_CONNECTED;
}