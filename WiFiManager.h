#pragma once

class WiFiManager
{
public:

    bool isConnected() const;

    void begin();

    void loop();

    bool connected() const;

};

extern WiFiManager WiFiMgr;