#include "DisplayManager.h"

DisplayManager Display;

//==================================================
// Initialize OLED
//==================================================

void DisplayManager::begin()
{
    display.begin();

    display.enableUTF8Print();

    display.clearBuffer();

    display.sendBuffer();
}

//==================================================
// Boot screen
//==================================================

void DisplayManager::bootScreen()
{
    display.clearBuffer();

    display.setFont(u8g2_font_logisoso20_tf);

    drawCentered("Weather", 26);
    drawCentered("Station", 56);

    display.setFont(u8g2_font_6x10_tf);

    drawCentered("ESP32-C6", 63);

    display.sendBuffer();
}

//==================================================
// OLED self test
//==================================================

void DisplayManager::selfTest()
{
    display.clearBuffer();

    display.setFont(u8g2_font_6x12_tf);

    display.drawStr(4, 10, "OLED SELF TEST");

    display.drawFrame(0, 16, 128, 40);

    display.drawCircle(18, 36, 8);

    display.drawBox(40, 28, 16, 16);

    display.drawLine(80, 22, 120, 50);

    display.drawStr(22, 63, "Display OK");

    display.sendBuffer();
}

//==================================================
// Connecting screen
//==================================================

void DisplayManager::drawConnectingScreen()
{
    display.clearBuffer();

    drawHeader("--:--", false);

    display.setFont(u8g2_font_helvB10_tf);

    drawCentered("Connecting", 30);

    drawCentered("WiFi...", 48);

    display.sendBuffer();
}

//==================================================
// WiFi connected screen
//==================================================

void DisplayManager::drawIPAddress(
    const char* ip)
{
    display.clearBuffer();

    drawHeader("--:--", true);

    display.setFont(u8g2_font_helvB10_tf);

    drawCentered("WiFi Connected", 28);

    display.setFont(u8g2_font_6x12_tf);

    drawCentered(ip, 48);

    display.sendBuffer();
}

//==================================================
// Main screen
//==================================================

void DisplayManager::drawReadyScreen(
    const char* time,
    bool wifi)
{
    display.clearBuffer();

    drawHeader(time, wifi);

    display.setFont(u8g2_font_helvB12_tf);

    drawCentered("System Ready", 34);

    display.setFont(u8g2_font_6x12_tf);

    drawCentered("Waiting...", 56);

    display.sendBuffer();
}

//==================================================
// Draw header
//==================================================

void DisplayManager::drawHeader(
    const char* time,
    bool wifi)
{
    display.setFont(u8g2_font_6x12_tf);

    display.drawStr(2, 10, time);

    if (wifi)
    {
        display.drawBox(111, 7, 2, 3);

        display.drawBox(115, 5, 2, 5);

        display.drawBox(119, 3, 2, 7);

        display.drawBox(123, 1, 2, 9);
    }

    display.drawHLine(0, 13, 128);
}

//==================================================
// Draw centered text
//==================================================

void DisplayManager::drawCentered(
    const char* text,
    int y)
{
    int width = display.getUTF8Width(text);

    display.drawUTF8(
        (128 - width) / 2,
        y,
        text);
}

//==================================================
// Clear buffer
//==================================================

void DisplayManager::clear()
{
    display.clearBuffer();
}

//==================================================
// Send buffer
//==================================================

void DisplayManager::update()
{
    display.sendBuffer();
}