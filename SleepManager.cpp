#include <WiFi.h>
#include <esp_sleep.h>

#include "DisplayManager.h"
#include "SleepManager.h"
#include <Arduino.h>
#include "ClockManager.h"
#include "config.h"

SleepManager Sleep;

//==================================================
// Initialize
//==================================================

void SleepManager::begin()
{
    sleepRequested = false;
}

//==================================================
// Main loop
//==================================================

void SleepManager::loop()
{
#if SLEEP_MODE_ENABLE

    sleepRequested = isSleepTime();

#else

    sleepRequested = false;

#endif
}

//==================================================
// Is sleep requested
//==================================================

bool SleepManager::shouldSleep() const
{
    return sleepRequested;
}

//==================================================
// Allow sleep
//==================================================

void SleepManager::allowSleep()
{
    if (!sleepRequested)
        return;

    sleepRequested = false;

    Display.sleep();

    delay(100);

    WiFi.disconnect(true);

    uint64_t sleepTime = calculateSleepTime();

    Serial.println();
    Serial.println("========== SLEEP ==========");
    Serial.print("Sleeping for ");
    Serial.print(sleepTime / 1000000ULL);
    Serial.println(" seconds");
    Serial.println("===========================");

    esp_sleep_enable_timer_wakeup(sleepTime);

    delay(100);

    esp_deep_sleep_start();
}

//==================================================
// Check sleep time
//==================================================

bool SleepManager::isSleepTime() const
{
    int current =
        Clock.getHour() * 60 +
        Clock.getMinute();

    int start =
        SLEEP_START_HOUR * 60 +
        SLEEP_START_MINUTE;

    int end =
        SLEEP_END_HOUR * 60 +
        SLEEP_END_MINUTE;

    // Интервал через полночь
    // Например: 23:00 -> 07:00

    if (start > end)
    {
        return
            current >= start ||
            current < end;
    }

    // Обычный интервал
    // Например: 12:00 -> 15:00

    return
        current >= start &&
        current < end;
}

//==================================================
// Calculate sleep time
//==================================================

uint64_t SleepManager::calculateSleepTime() const
{
    int current =
        Clock.getHour() * 60 +
        Clock.getMinute();

    int wake =
        SLEEP_END_HOUR * 60 +
        SLEEP_END_MINUTE;

    if (wake <= current)
        wake += 24 * 60;

    uint64_t minutes = wake - current;

    return
        minutes *
        60ULL *
        1000000ULL;
}