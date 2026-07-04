#pragma once

class WiFiManager
{
public:

    void begin();

    void loop();

    bool connected();

};

extern WiFiManager WiFiMgr;