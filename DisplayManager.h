#pragma once

#include <U8g2lib.h>

class DisplayManager
{
public:

    void begin();

    void bootScreen();

    void selfTest();

    void readyScreen();

    void clear();

    void update();

    void drawHeader(
        const char* time,
        bool wifi);

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C&
    oled();

private:

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C display =
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C(
            U8G2_R0,
            U8X8_PIN_NONE
        );
};

extern DisplayManager Display;