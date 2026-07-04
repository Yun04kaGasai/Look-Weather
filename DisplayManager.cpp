#include "DisplayManager.h"

DisplayManager Display;

void DisplayManager::begin()
{
    display.begin();

    display.enableUTF8Print();

    display.clearBuffer();

    display.sendBuffer();
}

void DisplayManager::bootScreen()
{
    display.clearBuffer();

    display.setFont(u8g2_font_logisoso20_tf);

    display.drawStr(
        10,
        26,
        "Weather"
    );

    display.drawStr(
        22,
        56,
        "Station"
    );

    display.setFont(
        u8g2_font_6x10_tf
    );

    display.drawStr(
        38,
        63,
        "ESP32-C6"
    );

    display.sendBuffer();
}

void DisplayManager::selfTest()
{
    display.clearBuffer();

    display.setFont(
        u8g2_font_6x12_tf
    );

    display.drawStr(
        4,
        10,
        "OLED SELF TEST"
    );

    display.drawFrame(
        0,
        16,
        128,
        40
    );

    display.drawCircle(
        18,
        36,
        8
    );

    display.drawBox(
        40,
        28,
        16,
        16
    );

    display.drawLine(
        80,
        22,
        120,
        50
    );

    display.drawStr(
        20,
        63,
        "Display OK"
    );

    display.sendBuffer();
}

void DisplayManager::readyScreen()
{
    display.clearBuffer();

    drawHeader(
        "--:--",
        false
    );

    display.setFont(
        u8g2_font_helvB12_tf
    );

    display.drawStr(
        10,
        36,
        "System Ready"
    );

    display.setFont(
        u8g2_font_6x12_tf
    );

    display.drawStr(
        28,
        58,
        "Waiting..."
    );

    display.sendBuffer();
}

void DisplayManager::clear()
{
    display.clearBuffer();
}

void DisplayManager::update()
{
    display.sendBuffer();
}

void DisplayManager::drawHeader(
        const char* time,
        bool wifi)
{
    display.setFont(
        u8g2_font_6x12_tf
    );

    display.drawStr(
        2,
        10,
        time
    );

    if(wifi)
    {
        display.drawFrame(111,5,2,5);

        display.drawFrame(116,3,2,7);

        display.drawFrame(121,1,2,9);
    }

    display.drawHLine(
        0,
        13,
        128
    );
}

U8G2_SSD1306_128X64_NONAME_F_HW_I2C&
DisplayManager::oled()
{
    return display;
}