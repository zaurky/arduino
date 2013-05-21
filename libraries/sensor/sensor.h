#ifndef sensor_h
#define sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define sensor_door_1 21816
#define sensor_door_4 9590072

class Sensor {
  public:
    Sensor();
    boolean know(long sensor_id);
    String get_name(long sensor_id);
};

#endif
