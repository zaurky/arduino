#ifndef utils_h
#define utils_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

int sensorPercent(int pin);
float sensorTemperature(int pin);

#endif
