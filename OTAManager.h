#pragma once

class OTAManager
{
public:

    // Initialize OTA service
    void begin();

    // Handle OTA events
    void loop();

};

extern OTAManager OTA;