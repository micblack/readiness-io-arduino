#include "ReadinessIoHttp.h"

ReadinessIoHttp::ReadinessIoHttp (String sensorid, String channel, String topic) {
  ReadinessIoHttp (sensorid, channel, topic, "", "", "");
}

ReadinessIoHttp::ReadinessIoHttp (String sensorid, String channel, String topic, String apikey, String version) {
  ReadinessIoHttp (sensorid, channel, topic, "", version, "");
}

ReadinessIoHttp::ReadinessIoHttp(String sensorid, String channel, String topic, String apikey, String version, String format)
{
  _sensorid = sensorid;
  _url = "http://" + channel + ".v1.readiness.io/" + topic + "/?d=esp8266";
  if(apikey != ""){
    _url += "&apikey=" + apikey;
  }
  if(format != ""){
    _url += "&format=" + format;
  }
  _version = version;
}

bool ReadinessIoHttp::publish(String payload){
  HTTPClient http;
  http.begin(_url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);
  String response = http.getString();
  Serial.println(response);
  http.end();
  return (httpCode < 400);
}

String ReadinessIoHttp::get(){
  HTTPClient http;
  http.begin(_url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET();
  String response = http.getString();
  http.end();
  return response;
}

void ReadinessIoHttp::connect () {
	// Not required
}

void ReadinessIoHttp::loop () {
	// Not required
}

bool ReadinessIoHttp::publishReading (float data){
  return publish("{\"sensor_id\":\""+_sensorid+"\", \"version\":\""+_version+"\", \"reading\":"+String(data, DEC)+"}");
}
bool ReadinessIoHttp::publishMessage (String message){
  return publish("{\"sensor_id\":\""+_sensorid+"\", \"version\":\""+_version+"\", \"message\":\""+message+"\"}");
}
bool ReadinessIoHttp::publishRaw (String payload){
  return publish(payload);
}
bool ReadinessIoHttp::publishJSON (JsonObject json){
  String output;
  json.printTo(output);
  return publish(output);
}

float ReadinessIoHttp::getReading (){
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(get());
  return root["reading"];
}
String ReadinessIoHttp::getMessage (){
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(get());
  return root["message"];
}
String ReadinessIoHttp::getRaw (){
  return get();
}
JsonObject& ReadinessIoHttp::getJSON (){
  StaticJsonBuffer<1024> jsonBuffer;
  return jsonBuffer.parseObject(get());
}


