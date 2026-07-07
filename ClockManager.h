#pragma once

class ClockManager
{
public:
    int getHour() const;

    int getMinute() const;

    void begin();

    void loop();

    const char* getTime();

private:

    char timeString[6] = "--:--";

    int hour = 0;

    int minute = 0;

    unsigned long lastUpdate = 0;
};

extern ClockManager Clock;