#include "ReadinessIoMqtt.h"
#include <functional>

ReadinessIoMqtt::ReadinessIoMqtt (String sensorid, String channel, String topic) {
  ReadinessIoMqtt (sensorid, channel, topic, "", "");
}

ReadinessIoMqtt::ReadinessIoMqtt (String sensorid, String channel, String topic, String version) {
  ReadinessIoMqtt (sensorid, channel, topic, version, "");
}

ReadinessIoMqtt::ReadinessIoMqtt(String sensorid, String channel, String topic, String version, String format)
{
  _sensorid = sensorid;
  _host = channel+".v1.readiness.io";
  if(format == ""){
    _path = "/"+topic;
  } else {
    _path = "/"+topic+"?format="+format;
  }
  _version = version;
  _topic = channel+'/'+topic;
  Serial.println(_topic);
}

/*void ReadinessIoMqtt::callback (WStype_t type, uint8_t * payload, size_t len) {
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

void ReadinessIoMqtt::connect () {
  mqtt.setClient(ReadinessIoCommon::client);
  mqtt.setServer(_host.c_str(), 1883);
  reconnect();
}

void ReadinessIoMqtt::reconnect() {
  // Loop until we're reconnected
  while (!mqtt.connected()) {
    if (mqtt.connect(_sensorid.c_str())) {
      // Connected
    } else {
      delay(5000); // Wait 5 seconds before retrying
    }
  }
}

void ReadinessIoMqtt::loop () {
  if (!mqtt.connected()) {
    reconnect();
  }
  mqtt.loop();
}

bool ReadinessIoMqtt::publishReading (float data){
  return mqtt.publish(_topic.c_str(), ("{\"sensor_id\":\""+_sensorid+"\", \"version\":\""+_version+"\", \"reading\":"+String(data, DEC)+"}").c_str());
}
bool ReadinessIoMqtt::publishMessage (String message){
  return mqtt.publish(_topic.c_str(), ("{\"sensor_id\":\""+_sensorid+"\", \"version\":\""+_version+"\", \"message\":\""+message+"\"}").c_str());
}
bool ReadinessIoMqtt::publishRaw (String payload){
  return mqtt.publish(_topic.c_str(), payload.c_str());
}
bool ReadinessIoMqtt::publishRaw (char* payload){
  return mqtt.publish(_topic.c_str(), payload);
}
bool ReadinessIoMqtt::publishJSON (JsonObject json){
  String output;
  json.printTo(output);
  return mqtt.publish(_topic.c_str(),output.c_str());
}

bool ReadinessIoMqtt::subscribe(std::function<void(char*, uint8_t*, unsigned int)> callback){
  mqtt.setCallback(callback);
  return mqtt.subscribe(_topic.c_str());
}

/*bool ReadinessIoMqtt::subscribeReading (ReadingEvent event){
  _ReadingEvent = event;
}
bool ReadinessIoMqtt::subscribeMessage (MessageEvent event){
  _MessageEvent = event;
}
bool ReadinessIoMqtt::subscribeRaw (RawEvent event){
  _RawEvent = event;
}
bool ReadinessIoMqtt::subscribeJSON (JSONEvent event){
  _JSONEvent = event;
}*/


