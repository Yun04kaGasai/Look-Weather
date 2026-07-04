#include "weather.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"

WeatherData weather;

unsigned long lastRequest = 0;

static String buildURL()
{
    return
        "https://api.openweathermap.org/data/2.5/forecast?q=" +
        String(CITY) +
        "," +
        String(COUNTRY) +
        "&units=metric&lang=ru&appid=" +
        String(API_KEY);
}
static bool requestWeather()
{
    HTTPClient http;

    http.begin(buildURL());

    int code = http.GET();

    if(code!=200)
    {
        Serial.printf("HTTP Error %d\n",code);

        http.end();

        return false;
    }

    String payload=http.getString();

    http.end();

    JsonDocument doc;

    auto err=deserializeJson(doc,payload);

    if(err)
    {
        Serial.println(err.c_str());

        return false;
    }

    JsonArray list=doc["list"];

    if(list.isNull())
        return false;
    JsonObject first=list[0];

    weather.currentTemp=first["main"]["temp"];

    weather.feelsLike=first["main"]["feels_like"];

    weather.minTemp=first["main"]["temp_min"];

    weather.maxTemp=first["main"]["temp_max"];

    weather.humidity=first["main"]["humidity"];

    weather.pressure=first["main"]["pressure"];

    weather.wind=first["wind"]["speed"];

    weather.rainProbability=
        int(first["pop"].as<float>()*100);

    strlcpy(
        weather.description,
        first["weather"][0]["description"] | "",
        sizeof(weather.description)
    );

    strlcpy(
        weather.icon,
        first["weather"][0]["icon"] | "",
        sizeof(weather.icon)
    );
    for(int i=0;i<8;i++)
    {
        JsonObject item=list[i];

        String dt=item["dt_txt"];

        dt=dt.substring(11,16);

        dt.toCharArray(
            weather.hourly[i].time,
            6
        );

        weather.hourly[i].temperature=
            item["main"]["temp"];

        weather.hourly[i].pop=
            int(item["pop"].as<float>()*100);

        strlcpy(
            weather.hourly[i].icon,
            item["weather"][0]["icon"] | "",
            sizeof(weather.hourly[i].icon)
        );
    }

    weather.lastUpdate=millis();

    weather.valid=true;

    Serial.println("Weather updated");

    return true;
}
void weatherBegin()
{
    requestWeather();
}

void weatherLoop()
{
    if(millis()-lastRequest<WEATHER_INTERVAL)
        return;

    lastRequest=millis();

    if(WiFi.status()==WL_CONNECTED)
    {
        requestWeather();
    }
}