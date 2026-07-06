class OTAManager
{
public:

    // Initialize OTA service
    void begin();

    // Handle OTA events
    void loop();

    // Returns true while OTA update is in progress
    bool isUpdating() const;

    // OTA state
    bool updating = false;
};

extern OTAManager OTA;