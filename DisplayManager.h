#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

class DisplayManager
{
public:

    // Initialize OLED
    void begin();

    // Boot screens
    void bootScreen();

    void selfTest();

    // WiFi screens
    void drawConnectingScreen();

    void drawIPAddress(
        const char* ip);

    // Main screen
    void drawReadyScreen(
        const char* time,
        bool wifi);

    // OTA screens
    void drawOTAProgress(
        uint8_t progress);

    void drawOTASuccess();

    void drawOTAError();

    // Buffer control
    void clear();

    void update();

private:

    // Draw top header
    void drawHeader(
        const char* time,
        bool wifi);

    // Draw centered text
    void drawCentered(
        const char* text,
        int y);

    // Draw progress bar
    void drawProgressBar(
        int x,
        int y,
        int width,
        int height,
        uint8_t percent);

private:

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C display =
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C(
            U8G2_R0,
            U8X8_PIN_NONE
        );
};

extern DisplayManager Display;