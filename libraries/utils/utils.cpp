#include "Arduino.h"
#include "utils.h"


// convert the analog value into a percent
int sensorPercent(int pin) {
    int val = analogRead(pin); // read the sensor (ranges from 0 to 1023)
    return map(val, 0, 1023, 0, 100); // percent will range from 0 to 100.
}
