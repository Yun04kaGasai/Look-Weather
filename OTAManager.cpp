#include "OTAManager.h"
#include "DisplayManager.h"

#include <Arduino.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

OTAManager OTA;

//==================================================
// Local web server
//==================================================

static AsyncWebServer server(80);

//==================================================
// Initialize OTA
//==================================================

void OTAManager::begin()
{
    Serial.println();
    Serial.println("Starting OTA server...");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(
            200,
            "text/html",
            "<h1>Weather Station</h1>"
            "<p>OTA server is running.</p>"
            "<a href=\"/update\">Open ElegantOTA</a>"
        );
    });

    ElegantOTA.begin(&server);
    //--------------------------------------------------
    // OTA callbacks
    //--------------------------------------------------

    ElegantOTA.onStart([]()
    {
        OTA.updating = true;

        Serial.println("OTA Update Started");

        Display.drawOTAProgress(0);
    });

    ElegantOTA.onProgress([](size_t current, size_t final)
    {
        uint8_t progress = (current * 100) / final;

        Display.drawOTAProgress(progress);
    });

    ElegantOTA.onEnd([](bool success)
    {
        OTA.updating = false;

        if (success)
        {
            Serial.println("OTA Update Complete");

            Display.drawOTASuccess();
        }
        else
        {
            Serial.println("OTA Update Failed");

            Display.drawOTAError();
        }

        delay(2000);
    });

    server.begin();

    Serial.println("OTA server started");
    Serial.println("Open http://<IP>/update");
}

//==================================================
// OTA loop
//==================================================

void OTAManager::loop()
{
    // Async server doesn't require polling
}

bool OTAManager::isUpdating() const
{
    return updating;
}