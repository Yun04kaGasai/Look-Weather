#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

class DisplayManager
{
public:

    void begin();

    void bootScreen();

    void clearBody();

    void drawHeader(
        const char *time,
        bool wifi);

    void drawCentered(
        const char *text,
        int y);

    void drawStatus(
        const char *line1,
        const char *line2);

    void update();

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C& getDisplay();

private:

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled =
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0,U8X8_PIN_NONE);

};

extern DisplayManager Display;