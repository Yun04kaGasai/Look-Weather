#include "DisplayManager.h"
#include <Wire.h>

DisplayManager Display;

//==================================================
// Initialize display
//==================================================

void DisplayManager::begin()
{
    Wire.begin(6, 7);

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
// WiFi connecting screen
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
// OTA progress screen
//==================================================

void DisplayManager::drawOTAProgress(
    uint8_t progress)
{
    display.clearBuffer();

    display.setFont(u8g2_font_6x12_tf);

    display.drawStr(2, 10, "OTA Update");

    display.drawHLine(0, 13, 128);

    display.setFont(u8g2_font_helvB10_tf);

    drawCentered("Updating...", 30);

    char percent[8];

    snprintf(
        percent,
        sizeof(percent),
        "%u%%",
        progress);

    drawCentered(percent, 46);

    drawProgressBar(
        14,
        52,
        100,
        8,
        progress);

    display.sendBuffer();
}

//==================================================
// OTA success screen
//==================================================

void DisplayManager::drawOTASuccess()
{
    display.clearBuffer();

    display.setFont(u8g2_font_6x12_tf);

    display.drawStr(2, 10, "OTA Update");

    display.drawHLine(0, 13, 128);

    display.setFont(u8g2_font_helvB10_tf);

    drawCentered("Update Complete", 34);

    display.setFont(u8g2_font_6x12_tf);

    drawCentered("Rebooting...", 54);

    display.sendBuffer();
}

//==================================================
// OTA error screen
//==================================================

void DisplayManager::drawOTAError()
{
    display.clearBuffer();

    display.setFont(u8g2_font_6x12_tf);

    display.drawStr(2, 10, "OTA Update");

    display.drawHLine(0, 13, 128);

    display.setFont(u8g2_font_helvB10_tf);

    drawCentered("Update Failed", 34);

    display.setFont(u8g2_font_6x12_tf);

    drawCentered("Please try again", 54);

    display.sendBuffer();
}

//==================================================
// Current weather screen (U8g2)
//==================================================

void DisplayManager::drawCurrentWeather(
    const char* time,
    float temperature,
    const String& description
)
{
    display.clearBuffer();

    drawHeader(time, true);

    // Temperature (big font)
    display.setFont(u8g2_font_10x20_t_cyrillic);

    char tempStr[8];
    snprintf(tempStr, sizeof(tempStr), "%d°", (int)temperature);

    drawCentered(tempStr, 38);

    // Description
    display.setFont(u8g2_font_6x12_t_cyrillic);
    drawCentered(description.c_str(), 58);

    display.sendBuffer();
}

//==================================================
// Min / Max screen (U8g2)
//==================================================

void DisplayManager::drawMinMax(
    const char* time,
    float minTemp,
    float maxTemp
)
{
    display.clearBuffer();

    drawHeader(time, true);

    display.setFont(u8g2_font_6x12_tf);

    // Min
    char minStr[16];
    snprintf(minStr, sizeof(minStr), "Min: %d°", (int)minTemp);
    display.drawUTF8(10, 32, minStr);

    // Max
    char maxStr[16];
    snprintf(maxStr, sizeof(maxStr), "Max: %d°", (int)maxTemp);
    display.drawUTF8(10, 52, maxStr);

    display.sendBuffer();
}

//==================================================
// Rain probability screen (U8g2)
//==================================================

void DisplayManager::drawRain(
    const char* time,
    int rainChance
)
{
    display.clearBuffer();

    drawHeader(time, true);

    display.setFont(u8g2_font_helvB10_tf);
    drawCentered("Rain chance", 28);

    display.setFont(u8g2_font_logisoso20_tf);

    char value[8];
    snprintf(value, sizeof(value), "%d%%", rainChance);

    drawCentered(value, 58);

    display.sendBuffer();
}

//==================================================
// Temperature graph screen (U8g2)
//==================================================

void DisplayManager::drawTemperatureGraph(
    const char* time,
    const ForecastPoint forecast[],
    uint8_t count
)
{
    display.clearBuffer();

    drawHeader(time, true);

    if (count < 2)
    {
        display.sendBuffer();
        return;
    }

    float minTemp = forecast[0].temperature;
    float maxTemp = forecast[0].temperature;

    for (uint8_t i = 1; i < count; i++)
    {
        if (forecast[i].temperature < minTemp)
            minTemp = forecast[i].temperature;

        if (forecast[i].temperature > maxTemp)
            maxTemp = forecast[i].temperature;
    }

    float range = maxTemp - minTemp;

    if (range < 1.0f)
        range = 1.0f;

    constexpr int graphX = 8;
    constexpr int graphY = 18;
    constexpr int graphW = 112;
    constexpr int graphH = 38;

    for (uint8_t i = 0; i < count - 1; i++)
    {
        int x1 = graphX + (graphW * i) / (count - 1);
        int x2 = graphX + (graphW * (i + 1)) / (count - 1);

        int y1 = graphY + graphH -
                 ((forecast[i].temperature - minTemp) * graphH / range);

        int y2 = graphY + graphH -
                 ((forecast[i + 1].temperature - minTemp) * graphH / range);

        display.drawLine(x1, y1, x2, y2);

        // Точки графика
        display.drawDisc(x1, y1, 2);
    }

    int lastX = graphX + graphW;

    int lastY = graphY + graphH -
                ((forecast[count - 1].temperature - minTemp) * graphH / range);

    display.drawDisc(lastX, lastY, 2);

    display.sendBuffer();
}

//==================================================
// Forecast screen (U8g2)
//==================================================

void DisplayManager::drawForecast(
    const char* time,
    const ForecastPoint forecast[],
    uint8_t count
)
{
    display.clearBuffer();

    drawHeader(time, true);

    display.setFont(u8g2_font_6x12_tf);

    uint8_t rows = (count > 4) ? 4 : count;

    for (uint8_t i = 0; i < rows; i++)
    {
        int y = 25 + (i * 10);

        char line[32];

        snprintf(
            line,
            sizeof(line),
            "%02u:00  %2d°  %2u%%",
            forecast[i].hour,
            (int)forecast[i].temperature,
            forecast[i].rainChance
        );

        display.drawUTF8(4, y, line);
    }

    display.sendBuffer();
}

//==================================================
// Draw progress bar
//==================================================

void DisplayManager::drawProgressBar(
    int x,
    int y,
    int width,
    int height,
    uint8_t percent)
{
    display.drawFrame(
        x,
        y,
        width,
        height);

    int fillWidth =
        (width - 2) * percent / 100;

    display.drawBox(
        x + 1,
        y + 1,
        fillWidth,
        height - 2);
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
        // WiFi signal icon

        display.drawBox(111, 7, 2, 3);

        display.drawBox(115, 5, 2, 5);

        display.drawBox(119, 3, 2, 7);

        display.drawBox(123, 1, 2, 9);
    }

    display.drawHLine(
        0,
        13,
        128);
}

//==================================================
// Draw centered text
//==================================================

void DisplayManager::drawCentered(
    const char* text,
    int y)
{
    int width =
        display.getUTF8Width(text);

    display.drawUTF8(
        (128 - width) / 2,
        y,
        text);
}

//==================================================
// Clear display buffer
//==================================================

void DisplayManager::clear()
{
    display.clearBuffer();
}

//==================================================
// Send buffer to display
//==================================================

void DisplayManager::update()
{
    display.sendBuffer();
}

//==================================================
// Display sleep
//==================================================

void DisplayManager::sleep()
{
    display.clearBuffer();
    display.sendBuffer();

    display.setPowerSave(1);
}

//==================================================
// Display wake
//==================================================

void DisplayManager::wake()
{
    display.setPowerSave(0);

    display.clearBuffer();
    display.sendBuffer();
}