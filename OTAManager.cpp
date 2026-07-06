#include "OTAManager.h"

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