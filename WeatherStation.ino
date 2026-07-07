#include "App.h"

App app;

void setup()
{
    Serial.begin(115200);
    delay(500);

    Serial.println("Setup started");

    app.begin();

    Serial.println("Setup finished");
}

void loop()
{
    app.loop();
}