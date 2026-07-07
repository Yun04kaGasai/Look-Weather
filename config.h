#pragma once

//==================================================
// Firmware information
//==================================================

#define FW_NAME            "Weather Station"
#define FW_VERSION         "0.5.0"
#define DEVICE_NAME        "weather-station"

//==================================================
// WiFi
//==================================================

#define WIFI_SSID          "MGTS_GPON_3C17"
#define WIFI_PASSWORD      "U3ES5JJ3"

//==================================================
// OLED
//==================================================

#define OLED_SDA           6
#define OLED_SCL           7

//==================================================
// Time
//==================================================

#define GMT_OFFSET         10800
#define DST_OFFSET         0

//==================================================
// Sleep mode
//==================================================

#define SLEEP_MODE_ENABLE      true

#define SLEEP_START_HOUR       23
#define SLEEP_START_MINUTE     4

#define SLEEP_END_HOUR         7
#define SLEEP_END_MINUTE       0

//==================================================
// OpenWeather API
//==================================================

#define OPENWEATHER_CURRENT_URL    "https://api.openweathermap.org/data/2.5/weather"

#define OPENWEATHER_FORECAST_URL   "https://api.openweathermap.org/data/2.5/forecast"

//==================================================
// Weather
//==================================================

#define WEATHER_API_KEY            "7e9d8f58a1562ff2d7863b39fda8691b"

#define WEATHER_LATITUDE           "55.8752"
#define WEATHER_LONGITUDE          "37.5106"

#define WEATHER_LANGUAGE           "ru"

#define WEATHER_UNITS              "metric"

#define WEATHER_UPDATE_INTERVAL    (15UL * 60UL * 1000UL)

//==================================================
// Network
//==================================================

#define HTTP_TIMEOUT               10000