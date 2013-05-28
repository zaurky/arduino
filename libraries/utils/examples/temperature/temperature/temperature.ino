#include <RCSwitch.h>
#include <blink2.h>

int tmpPin = 0;
int lumPin = 1;

void setup() {
  Serial.begin(9600);
}

void loop() { 
  float tempC = sensorTemperature(tmpPin);
  Serial.print(tempC);
  Serial.print(" °C, lum : ");
  
  int lumRead = analogRead(lumPin);
  Serial.println(lumRead);
  
  delay(1000);
}
