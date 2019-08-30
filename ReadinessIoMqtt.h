#ifndef ReadinessIoMqtt_h
#define ReadinessIoMqtt_h

#include "ReadinessIoCommon.h"
#include <PubSubClient.h>
#include <functional>

class ReadinessIoMqtt: public ReadinessIoCommon {
  public:
    #ifdef __AVR__
      typedef void (*ReadingEvent)(float data); //Common
      typedef void (*MessageEvent)(String message); //Common, possibly wrong
      typedef void (*RawEvent)(String payload); //Common
      typedef void (*JSONEvent)(JsonObject& json); //Common
    #else
      typedef std::function<void (float data)> ReadingEvent;
      typedef std::function<void (String message)> MessageEvent;
      typedef std::function<void (String payload)> RawEvent;
      typedef std::function<void (JsonObject& json)> JSONEvent;
    #endif
    
    ReadinessIoMqtt(String sensorid, String channel, String topic, String version, String format);
    ReadinessIoMqtt(String sensorid, String channel, String topic, String version);
    ReadinessIoMqtt(String sensorid, String channel, String topic);
    void connect ();
    void loop ();
    
    bool publishReading (float reading);
    bool publishMessage (String message);
    bool publishRaw (String payload);
    bool publishRaw (char* payload);
    bool publishJSON (JsonObject json);
    
    bool subscribe(std::function<void(char*, uint8_t*, unsigned int)> callback);
    //bool subscribeReading (ReadingEvent event);
    //bool subscribeMessage (MessageEvent event);
    //bool subscribeRaw (RawEvent event);
    //bool subscribeJSON (JSONEvent event);

  private:
    PubSubClient mqtt;
    void reconnect ();
    String _sensorid;
    String _host;
    String _path;
    String _version;
    String _topic;
    
    
    
    //ReadingEvent _ReadingEvent;
    //MessageEvent _MessageEvent;
    //RawEvent _RawEvent;
    //JSONEvent _JSONEvent;
    
    /*virtual void runCallbacks(float reading, String message, String payload, JsonObject* json) {
        if(_ReadingEvent) {
            _ReadingEvent(reading);
        }
        if(_MessageEvent) {
            _MessageEvent(message);
        }
        if(_RawEvent) {
            _RawEvent(payload, 0);
        }
        if(_JSONEvent) {
            _JSONEvent(json);
        }
    }*/
};

#endif
