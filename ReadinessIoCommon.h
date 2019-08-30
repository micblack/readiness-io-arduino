#ifndef ReadinessIoCommon_h
#define ReadinessIoCommon_h

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class ReadinessIoCommon
{
  public:
    //ReadinessIoCommon();
    void wifi (char* ssid, char* password);
	void wifi (char* ssid, char* password, int led);
    bool jsonreading ();
    WiFiClient client;
  private:

};

#endif
