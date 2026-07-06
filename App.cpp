#include "App.h"

#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "DisplayManager.h"
#include "WiFiManager.h"
#include "ClockManager.h"
#include "OTAManager.h"

//==================================================
// Initialize application
//==================================================

void App::begin()
{
    Serial.begin(115200);

    Wire.begin(
        OLED_SDA,
        OLED_SCL
    );

    // Initialize display
    Display.begin();

    Display.bootScreen();
    delay(1500);

    Display.selfTest();
    delay(2500);

    // Connect to WiFi
    WiFiMgr.begin();

    // Initialize clock
    Clock.begin();

    // Initialize OTA
    OTA.begin();

    Serial.println("Application started");
}

//==================================================
// Main loop
//==================================================

void App::loop()
{
    WiFiMgr.loop();

    Clock.loop();

    OTA.loop();

    if (!OTA.isUpdating())
    {
        Display.drawReadyScreen(
            Clock.getTime(),
            WiFiMgr.connected()
        );
    }
}