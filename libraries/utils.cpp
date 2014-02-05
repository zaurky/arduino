#include "Arduino.h"
#include "utils.h"


// convert the analog value into a percent
int sensorPercent(int pin) {
    int val = analogRead(pin); // read the sensor (ranges from 0 to 1023)
    return map(val, 0, 1023, 0, 100); // percent will range from 0 to 100.
}


// convert the analog read into a temperature
float sensorTemperature(int pin) {
    int read = analogRead(pin);
    float voltage = read * 5.0;
    voltage /= 1024.0;
    float temperature = (voltage - 0.5) * 100;
    return temperature;
}


// read from serial
int readSerialInt() {
    int sb = 47;
    if (Serial.available()) {
        sb = Serial.read();
    }
    // ugly convert from ascii to latin1 ...
    return sb - 48;
}

void readSerialString(char* serInString) {
    int sb;
    int serInIndx = 0;
    if (Serial.available()) {
        while (Serial.available()){
            sb = Serial.read();
            serInString[serInIndx] = sb;
            serInIndx++;
        }
    }
}
