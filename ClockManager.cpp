#include "ClockManager.h"

#include <Arduino.h>
#include <time.h>

#include "config.h"

ClockManager Clock;

void ClockManager::begin()
{
    configTime(
        GMT_OFFSET,
        DST_OFFSET,
        "pool.ntp.org",
        "time.google.com"
    );
}

void ClockManager::loop()
{
    if (millis() - lastUpdate < 1000)
        return;

    lastUpdate = millis();

    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
        return;

    hour = timeinfo.tm_hour;
    minute = timeinfo.tm_min;

    strftime(
        timeString,
        sizeof(timeString),
        "%H:%M",
        &timeinfo
    );
}

const char* ClockManager::getTime()
{
    return timeString;
}

int ClockManager::getHour() const
{
    return hour;
}

int ClockManager::getMinute() const
{
    return minute;
}