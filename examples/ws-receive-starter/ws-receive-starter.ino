#include <Arduino.h>
#include <ReadinessIoWebsockets.h>
#include "config.h"

const uint8_t  LED_PIN   = LED_BUILTIN;  // The GPIO that your status LED is attached to
const int      RELAY_PIN = D6;           // The GPIO that your relay is attached to
const uint16_t BAUD      = 9600;         // Debugging serial baud rate

const uint16_t TURN_ON_AFTER = 10000;    // How long to wait before turning LED on

ReadinessIoWebsockets ws(SENSOR_ID,CHANNEL_ID,TOPIC,VERSION,FORMAT);

void wsCallback(WStype_t type, uint8_t * payload, size_t length) {

  if(type == WStype_DISCONNECTED){
      Serial.printf("[WSc] Disconnected\n");
  } else if(type == WStype_CONNECTED){
      Serial.printf("[WSc] Connected to url: %s\n", payload);
  } else if(type == WStype_TEXT){
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(payload);
      uint16_t reading = root["reading"];
      logic(reading);
   }
}

void logic(uint16 time_since_starting) {

  if(time_since_starting > TURN_ON_AFTER){
    Serial.println("Relay ON");
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.println("Relay OFF");
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void setup() {
  
  Serial.begin(BAUD);
  Serial.println("Begin");
  pinMode(LED_PIN, OUTPUT);  

  ws.connect();
  ws.subscribe(wsCallback);
}

void loop() {
  
  ws.loop();
}
