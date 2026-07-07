#include "WeatherManager.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"

WeatherManager Weather;

//==================================================
// Initialize weather manager
//==================================================

void WeatherManager::begin()
{
    ready = false;
    error = false;

    // Чтобы первое обновление произошло сразу
    lastUpdate = millis() - WEATHER_UPDATE_INTERVAL;
}
//==================================================
// Weather manager loop
//==================================================

void WeatherManager::loop()
{
    if (!WiFi.isConnected())
        return;

    if (millis() - lastUpdate < WEATHER_UPDATE_INTERVAL)
        return;

    update();
}

//==================================================
// Update weather
//==================================================

bool WeatherManager::update()
{
    Serial.println("Updating weather...");

    if (!updateCurrent())
    {
        error = true;
        return false;
    }

    if (!updateForecast())
    {
        error = true;
        return false;
    }

    ready = true;
    error = false;
    lastUpdate = millis();

    Serial.println("Weather updated.");

    return true;
}

//==================================================
// Update current weather
//==================================================

bool WeatherManager::updateCurrent()
{
    HTTPClient http;

    String url =
        String(OPENWEATHER_CURRENT_URL) +
        "?lat=" + WEATHER_LATITUDE +
        "&lon=" + WEATHER_LONGITUDE +
        "&appid=" + WEATHER_API_KEY +
        "&units=" + WEATHER_UNITS +
        "&lang=" + WEATHER_LANGUAGE;

    Serial.println("Request current weather...");
    Serial.println(url);

    http.setTimeout(HTTP_TIMEOUT);

    if (!http.begin(url))
    {
        Serial.println("HTTP begin failed.");

        return false;
    }

    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK)
    {
        Serial.print("HTTP Error: ");
        Serial.println(httpCode);

        http.end();

        return false;
    }

    String payload = http.getString();

    Serial.println("====== JSON ======");
    Serial.println(payload);
    Serial.println("==================");

    http.end();

    return parseCurrent(payload);
}

//==================================================
// Update forecast
//==================================================

bool WeatherManager::updateForecast()
{
    HTTPClient http;

    String url =
        String(OPENWEATHER_FORECAST_URL) +
        "?lat=" + WEATHER_LATITUDE +
        "&lon=" + WEATHER_LONGITUDE +
        "&appid=" + WEATHER_API_KEY +
        "&units=" + WEATHER_UNITS +
        "&lang=" + WEATHER_LANGUAGE;

    Serial.println("Request forecast...");
    Serial.println(url);

    http.setTimeout(HTTP_TIMEOUT);

    if (!http.begin(url))
    {
        Serial.println("HTTP begin failed.");

        return false;
    }

    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK)
    {
        Serial.print("HTTP Error: ");
        Serial.println(httpCode);

        http.end();

        return false;
    }

    String payload = http.getString();

    http.end();

    return parseForecast(payload);
}

//==================================================
// Parse current weather
//==================================================

bool WeatherManager::parseCurrent(const String& json)
{
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, json);

    if (error)
    {
        Serial.println("Current weather JSON parse failed.");

        return false;
    }

    weather.temperature = doc["main"]["temp"] | 0.0f;
    weather.feelsLike  = doc["main"]["feels_like"] | 0.0f;
    weather.humidity   = doc["main"]["humidity"] | 0;
    weather.pressure   = doc["main"]["pressure"] | 0;

    JsonArray weatherArray = doc["weather"];

    if (weatherArray.isNull() || weatherArray.size() == 0)
    {
        Serial.println("Weather array is empty!");
        return false;
    }

    JsonObject weatherObj = weatherArray[0];

    weather.description = weatherObj["description"].as<String>();
    weather.icon = weatherObj["icon"].as<String>();

    Serial.print("Parsed description: ");
    Serial.println(weather.description);

    Serial.print("Parsed icon: ");
    Serial.println(weather.icon);

    return true;
}

//==================================================
// Parse forecast
//==================================================

bool WeatherManager::parseForecast(const String& json)
{
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, json);

    if (error)
    {
        Serial.println("Forecast JSON parse failed.");

        return false;
    }

    JsonArray list = doc["list"];

    uint8_t index = 0;

    for (JsonObject item : list)
    {
        if (index >= 8)
            break;

        weather.forecast[index].temperature =
            item["main"]["temp"] | 0.0f;

        weather.forecast[index].rainChance =
            (item["pop"].as<float>() * 100.0f);

        const char* dt = item["dt_txt"];

        if (dt != nullptr)
        {
            weather.forecast[index].hour =
                (dt[11] - '0') * 10 +
                (dt[12] - '0');
        }

        index++;
    }

    return true;
}

//==================================================
// Status
//==================================================

bool WeatherManager::isReady() const
{
    return ready;
}

bool WeatherManager::hasError() const
{
    return error;
}

unsigned long WeatherManager::getLastUpdate() const
{
    return lastUpdate;
}

//==================================================
// Current weather
//==================================================

float WeatherManager::getTemperature() const
{
    return weather.temperature;
}

float WeatherManager::getFeelsLike() const
{
    return weather.feelsLike;
}

int WeatherManager::getHumidity() const
{
    return weather.humidity;
}

int WeatherManager::getPressure() const
{
    return weather.pressure;
}

String WeatherManager::getDescription() const
{
    return weather.description;
}

String WeatherManager::getIcon() const
{
    return weather.icon;
}

//==================================================
// Today's forecast
//==================================================

float WeatherManager::getTempMin() const
{
    float value = weather.forecast[0].temperature;

    for (uint8_t i = 1; i < 8; i++)
    {
        if (weather.forecast[i].temperature < value)
            value = weather.forecast[i].temperature;
    }

    return value;
}

float WeatherManager::getTempMax() const
{
    float value = weather.forecast[0].temperature;

    for (uint8_t i = 1; i < 8; i++)
    {
        if (weather.forecast[i].temperature > value)
            value = weather.forecast[i].temperature;
    }

    return value;
}

int WeatherManager::getRainChance() const
{
    int value = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        if (weather.forecast[i].rainChance > value)
            value = weather.forecast[i].rainChance;
    }

    return value;
}

//==================================================
// Forecast
//==================================================

ForecastPoint WeatherManager::getForecastPoint(uint8_t index) const
{
    if (index >= 8)
        return ForecastPoint();

    return weather.forecast[index];
}