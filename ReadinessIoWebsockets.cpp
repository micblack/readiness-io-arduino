#include "ReadinessIoWebsockets.h"

ReadinessIoWebsockets::ReadinessIoWebsockets (String sensorid, String channel, String topic) {
  ReadinessIoWebsockets (sensorid, channel, topic, "", "");
}

ReadinessIoWebsockets::ReadinessIoWebsockets (String sensorid, String channel, String topic, String version) {
  ReadinessIoWebsockets (sensorid, channel, topic, version, "");
}

ReadinessIoWebsockets::ReadinessIoWebsockets(String sensorid, String channel, String topic, String version, String format)
{
  _sensorid = sensorid;
  _host = channel+".v1.readiness.io";
  if(format == ""){
    _path = "/"+topic;
  } else {
    _path = "/"+topic+"?format="+format;
  }
  _version = version;
}

/*void ReadinessIoWebsockets::callback (WStype_t type, uint8_t * payload, size_t len) {
  if(type == WStype_TEXT) {
    if(_ReadingEvent || _MessageEvent || _RawEvent){
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(payload);
      if(_ReadingEvent){
        _ReadingEvent(float(root["reading"]));
      }
      if(_MessageEvent){
        String message = root["message"];
        _MessageEvent(message);
      }
      if(_JSONEvent){
        _JSONEvent(root);
      }
    }
    //if(_RawEvent){ 
    //  _RawEvent(payload, len);
    //}
  }
}*/

void ReadinessIoWebsockets::connect () {
	webSocket.begin(_host, 80, _path);
  webSocket.setReconnectInterval(1000);
  while(!webSocket.sendPing()){
    delay(100);
    webSocket.loop();
  }
  lastping = millis();
}

void ReadinessIoWebsockets::loop () {
  webSocket.loop();
  unsigned long time = millis();
  if(time > lastping + 90000){
    lastping = time;
    webSocket.sendPing();
  }
}

bool ReadinessIoWebsockets::publishReading (float data){
  return webSocket.sendTXT("{\"sensor_id\":\""+_sensorid+"\", \"version\":\""+_version+"\", \"reading\":"+String(data, DEC)+"}");
}
bool ReadinessIoWebsockets::publishMessage (String message){
  return webSocket.sendTXT("{\"sensor_id\":\""+_sensorid+"\", \"version\":\""+_version+"\", \"message\":\""+message+"\"}");
}
bool ReadinessIoWebsockets::publishRaw (String payload){
  return webSocket.sendTXT(payload);
}
bool ReadinessIoWebsockets::publishJSON (JsonObject json){
  String output;
  json.printTo(output);
  return webSocket.sendTXT(output.c_str());
}

bool ReadinessIoWebsockets::subscribe(WebSocketsClient::WebSocketClientEvent callback){
  webSocket.onEvent(callback);
  return true;
}

/*bool ReadinessIoWebsockets::subscribeReading (ReadingEvent event){
  _ReadingEvent = event;
}
bool ReadinessIoWebsockets::subscribeMessage (MessageEvent event){
  _MessageEvent = event;
}
bool ReadinessIoWebsockets::subscribeRaw (RawEvent event){
  _RawEvent = event;
}
bool ReadinessIoWebsockets::subscribeJSON (JSONEvent event){
  _JSONEvent = event;
}*/


