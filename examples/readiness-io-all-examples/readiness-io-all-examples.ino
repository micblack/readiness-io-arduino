#include <Arduino.h>
#include "ReadinessIoHttp.h"
#include "ReadinessIoWebsockets.h"
#include "ReadinessIoMqtt.h"
#include "config.h"

float reading = 0;

ReadinessIoHttp http(SENSOR_ID,CHANNEL_ID,TOPIC,VERSION,FORMAT);
ReadinessIoWebsockets ws(SENSOR_ID,CHANNEL_ID,TOPIC,VERSION,FORMAT);
ReadinessIoMqtt mqtt(SENSOR_ID,CHANNEL_ID,TOPIC,VERSION,FORMAT);



void wsCallback(WStype_t type, uint8_t * payload, size_t length) {
  if(type == WStype_DISCONNECTED){
      Serial.printf("[WSc] Disconnected!\n");
  } else if(type == WStype_CONNECTED){
      Serial.printf("[WSc] Connected to url: %s\n", payload);
  } else if(type == WStype_TEXT){
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(payload);
      float reading = root["reading"];
      Serial.print("WS: ");
      Serial.println(reading, DEC);
   }
   ws.jsonreading();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.println("MQTT CALL BACK");
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(payload,length);
    float reading = root["reading"];
    Serial.print("MQTT: ");
    Serial.println(reading, DEC);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  http.wifi(WIFI_SSID, WIFI_PASS);
  Serial.println();

  Serial.println("HTTP Reads");
  Serial.print("Reading: ");
  Serial.println(http.getReading());
  Serial.print("Message: ");
  Serial.println(http.getMessage());
  Serial.print("Raw: ");
  Serial.println(http.getRaw());

  ws.connect();
  Serial.println(ws.subscribe(wsCallback));
  mqtt.connect();
  Serial.println(mqtt.subscribe(mqttCallback));

  delay(1000);
  mqtt.loop();
  ws.loop();

  Serial.println("HTTP Sends");
  // Optional channel and topic dont work on WebSocket, Optional format doesnt work on WebSocket or MQTT
  Serial.println(http.publishReading(10));
  mqtt.loop();
  ws.loop();
  Serial.println(http.publishMessage("http"));
  mqtt.loop();
  ws.loop();
  Serial.println(http.publishRaw("{\"json\":\"http\"}"));
  mqtt.loop();
  ws.loop();
  
  delay(1000);
  mqtt.loop();
  ws.loop();

  Serial.println("WS Sends");
  Serial.println(ws.publishReading(11));
  delay(1000);
  mqtt.loop();
  ws.loop();
  Serial.println(ws.publishMessage("websocket"));
  delay(1000);
  mqtt.loop();
  ws.loop();
  Serial.println(ws.publishRaw("{\"json\":\"websocket\"}"));
  delay(1000);
  mqtt.loop();
  ws.loop();

  delay(1000);
  mqtt.loop();
  ws.loop();

  Serial.println("MQTT Sends");
  Serial.println(mqtt.publishReading(12));
  delay(1000);
  mqtt.loop();
  ws.loop();
  Serial.println(mqtt.publishMessage("mqtt"));
  delay(1000);
  mqtt.loop();
  ws.loop();
  Serial.println(mqtt.publishRaw("{\"json\":\"mqtt\"}"));
  delay(1000);
  mqtt.loop();
  ws.loop();
}

void loop() {
  ws.loop();
  mqtt.loop();
  
  // capture the value of pin 1, send it along
  /*float newreading = digitalRead(D1);
  if(newreading != reading){
    reading = newreading;
    Serial.print("Sending data: ");
    Serial.println(reading);
    http.publishReading(reading);
  }*/
}
