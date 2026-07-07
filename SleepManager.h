#include <Arduino.h>

class SleepManager
{
public:
    void begin();
    void loop();

    // Нужно ли переходить в режим сна
    bool shouldSleep() const;

    // Разрешить переход в сон
    void allowSleep();

private:
    bool isSleepTime() const;
    uint64_t calculateSleepTime() const;
    void enterDeepSleep();

private:
    bool sleepRequested = false;
};

extern SleepManager Sleep;