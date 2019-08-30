#include <Arduino.h>
#include <ReadinessIoHttp.h>
#include "config.h"

const uint8_t  LED_PIN  = LED_BUILTIN;  // The GPIO that your status LED is attached to
const uint16_t BAUD     = 9600;         // Debugging serial baud rate

ReadinessIoHttp http(SENSOR_ID,CHANNEL_ID,TOPIC,VERSION,FORMAT);

void setup() {
  
  Serial.begin(BAUD);
  Serial.println("Begin");
  pinMode(LED_PIN, OUTPUT);  

  http.wifi(WIFI_SSID, WIFI_PASS, LED_PIN);
}

void loop() {

  uint16_t time_since_starting = millis();
  
  Serial.print("Time since starting: ");
  Serial.println(time_since_starting);

  if (http.publishReading(time_since_starting)) {
    Serial.println("/ Now readiness.io knows");
  } else {
    Serial.println("X There was an error trying to send time_since_starting");
  }

  delay(5000); // This is bad, let's explore why
}