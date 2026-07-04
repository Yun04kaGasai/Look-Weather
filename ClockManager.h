#pragma once

class ClockManager
{
public:

    void begin();

    void loop();

    const char* getTime();

private:

    char timeString[6] = "--:--";

    unsigned long lastUpdate = 0;
};

extern ClockManager Clock;