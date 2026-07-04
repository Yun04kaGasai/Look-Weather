#include "App.h"

#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "DisplayManager.h"
#include "WiFiManager.h"

void App::begin()
{
    Serial.begin(115200);

    Wire.begin(
        OLED_SDA,
        OLED_SCL
    );

    Display.begin();

    Display.bootScreen();

    delay(1500);

    Display.selfTest();

    delay(2500);

    WiFiMgr.begin();

    Display.readyScreen();
}

void App::loop()
{
    WiFiMgr.loop();
}