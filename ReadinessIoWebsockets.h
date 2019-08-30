#ifndef ReadinessIoWebsockets_h
#define ReadinessIoWebsockets_h

#include "ReadinessIoCommon.h"
#include <WebSocketsClient.h>


class ReadinessIoWebsockets: public ReadinessIoCommon {
  public:
    /*#ifdef __AVR__
      typedef void (*ReadingEvent)(float data); //Common
      typedef void (*MessageEvent)(String message); //Common, possibly wrong
      typedef void (*RawEvent)(String payload); //Common
      typedef void (*JSONEvent)(JsonObject& json); //Common
    #else
      typedef std::function<void (float data)> ReadingEvent;
      typedef std::function<void (String message)> MessageEvent;
      typedef std::function<void (String payload)> RawEvent;
      typedef std::function<void (JsonObject& json)> JSONEvent;
    #endif*/
    
    ReadinessIoWebsockets(String sensorid, String channel, String topic, String version, String format);
  	ReadinessIoWebsockets(String sensorid, String channel, String topic, String version);
    ReadinessIoWebsockets(String sensorid, String channel, String topic);
  	//void callback(WStype_t type, uint8_t * payload, size_t len);
  	void connect ();
  	void loop ();
    
    
  	bool publishReading (float reading);
    bool publishMessage (String message);
    bool publishRaw (String payload);
    bool publishJSON (JsonObject json);
    
    
    bool subscribe(WebSocketsClient::WebSocketClientEvent callback);
    //bool subscribeReading (ReadingEvent event);
    //bool subscribeMessage (MessageEvent event);
    //bool subscribeRaw (RawEvent event);
    //bool subscribeJSON (JSONEvent event);

  private:
  	WebSocketsClient webSocket;
    String _sensorid;
    String _host;
    String _path;
    String _version;
    unsigned long lastping;
    
    
    
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
