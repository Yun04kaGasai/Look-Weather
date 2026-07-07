#pragma once

#include <Arduino.h>

//==================================================
// Forecast point
//==================================================

struct ForecastPoint
{
    uint8_t hour = 0;

    float temperature = 0.0f;

    uint8_t rainChance = 0;
};

//==================================================
// Weather data
//==================================================

struct WeatherData
{
    // Current weather

    float temperature = 0.0f;

    float feelsLike = 0.0f;

    float tempMin = 0.0f;

    float tempMax = 0.0f;

    int humidity = 0;

    int pressure = 0;

    int rainChance = 0;

    String description = "";

    String icon = "";

    // Forecast

    ForecastPoint forecast[8];
};

//==================================================
// Weather Manager
//==================================================

class WeatherManager
{
public:

    // Initialize weather service
    void begin();

    // Update weather automatically
    void loop();

    // Force weather update
    bool update();

    // Status
    bool isReady() const;

    bool hasError() const;

    unsigned long getLastUpdate() const;

    // Current weather
    float getTemperature() const;

    float getFeelsLike() const;

    float getTempMin() const;

    float getTempMax() const;

    int getHumidity() const;

    int getPressure() const;

    int getRainChance() const;

    String getDescription() const;

    String getIcon() const;

    // Forecast
    ForecastPoint getForecastPoint(uint8_t index) const;

private:

    bool updateCurrent();

    bool updateForecast();

    bool parseCurrent(const String& json);

    bool parseForecast(const String& json);

private:

    WeatherData weather;

    bool ready = false;

    bool error = false;

    unsigned long lastUpdate = 0;
};

extern WeatherManager Weather;