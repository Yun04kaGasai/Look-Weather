#include "App.h"

#include "ClockManager.h"
#include "DisplayManager.h"
#include "OTAManager.h"
#include "WeatherManager.h"
#include "WiFiManager.h"
#include "SleepManager.h"

namespace
{
    uint8_t currentScreen = 0;

    unsigned long lastScreenChange = 0;

    constexpr unsigned long SCREEN_TIME = 5000;
}

void App::begin()
{
    Display.begin();

    // Display.sleep();

    // delay(5000);

    // Display.wake();

    // Display.bootScreen();

    // delay(2000);

    WiFiMgr.begin();

    Clock.begin();

    OTA.begin();

    Weather.begin();

    Sleep.begin();
}

void App::loop()
{
    WiFiMgr.loop();

    Clock.loop();

    OTA.loop();

    Sleep.loop();

    Sleep.loop();

    if (Sleep.shouldSleep())
    {
        Sleep.allowSleep();
        return;
    }

    Weather.loop();

    // OTA has the highest priority
    if (OTA.isUpdating())
    {
        // Пока процент обновления не передаётся
        Display.drawOTAProgress(0);
        return;
    }

    // Serial.print("Weather ready = ");
    // Serial.println(Weather.isReady());

    // Wait until weather data is available
    if (!Weather.isReady())
    {
        Display.drawReadyScreen(
            Clock.getTime(),
            WiFiMgr.isConnected()
        );

        return;
    }

    // Change screen every few seconds
    if (millis() - lastScreenChange >= SCREEN_TIME)
    {
        lastScreenChange = millis();

        currentScreen++;

        if (currentScreen >= 5)
            currentScreen = 0;
    }

    switch (currentScreen)
    {
        case 0:
            Display.drawCurrentWeather(
                Clock.getTime(),
                Weather.getTemperature(),
                Weather.getDescription()
            );
            break;

        case 1:
            Display.drawMinMax(
                Clock.getTime(),
                Weather.getTempMin(),
                Weather.getTempMax()
            );
            break;

        case 2:
            Display.drawRain(
                Clock.getTime(),
                Weather.getRainChance()
            );
            break;

        case 3:
        {
            ForecastPoint forecast[8];

            for (uint8_t i = 0; i < 8; i++)
                forecast[i] = Weather.getForecastPoint(i);

            Display.drawTemperatureGraph(
                Clock.getTime(),
                forecast,
                8
            );

            break;
        }

        case 4:
        {
            ForecastPoint forecast[8];

            for (uint8_t i = 0; i < 8; i++)
                forecast[i] = Weather.getForecastPoint(i);

            Display.drawForecast(
                Clock.getTime(),
                forecast,
                8
            );

            break;
        }
    }
}