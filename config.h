#pragma once

//==================================================
// Firmware information
//==================================================

#define FW_NAME            "Weather Station"
#define FW_VERSION         "0.4.1"
#define DEVICE_NAME        "weather-station"

//==================================================
// WiFi
//==================================================

#define WIFI_SSID          ""
#define WIFI_PASSWORD      ""

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
// OpenWeather
// (will be used in v0.5)
//==================================================

#define WEATHER_API_KEY    ""
#define WEATHER_LAT        "0.0000"
#define WEATHER_LON        "0.0000"