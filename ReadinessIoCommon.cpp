#include "ReadinessIoCommon.h"

void ReadinessIoCommon::wifi(char* ssid, char* password) {
  wifi(ssid, password, LED_BUILTIN);
}

void ReadinessIoCommon::wifi(char* ssid, char* password, int led) {
  pinMode(led, OUTPUT);

  uint8_t LED_ON  = HIGH;
  uint8_t LED_OFF = LOW;

  if (led == LED_BUILTIN) {
    // NodeMCU has an inverted LED for some reason
    LED_ON  = !LED_ON;
    LED_OFF = !LED_OFF;
  }

  digitalWrite(led, LED_OFF);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, LED_ON);
    delay(100);
    digitalWrite(led, LED_OFF);
    delay(100);
  Serial.println(".");
  }
  
  digitalWrite(led, LED_OFF);
}

bool ReadinessIoCommon::jsonreading(){
  return true;
}