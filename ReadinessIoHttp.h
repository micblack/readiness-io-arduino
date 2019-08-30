#ifndef ReadinessIoHttp_h
#define ReadinessIoHttp_h

#include "ReadinessIoCommon.h"
#include <ESP8266HTTPClient.h>


class ReadinessIoHttp: public ReadinessIoCommon {
  public:
    ReadinessIoHttp(String sensorid, String channel, String topic, String apikey, String version, String format);
  	ReadinessIoHttp(String sensorid, String channel, String topic, String apikey, String version);
    ReadinessIoHttp(String sensorid, String channel, String topic);
  	void connect ();
  	void loop ();
    
  	bool publishReading (float reading);
    bool publishMessage (String message);
    bool publishRaw (String payload);
    bool publishJSON (JsonObject json);
    
    float getReading ();
    String getMessage ();
    String getRaw ();
    JsonObject& getJSON ();

  private:
    bool publish(String payload);
    String get();
    String _sensorid;
    String _url;
    String _version;

};

#endif
