#ifndef sensor_h
#define sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define sensor_door_1 21816
#define sensor_door_4 9590072

#define debounceDelay 1000

class Sensor {
  public:
    Sensor();
    int get_uuid(long sensor_id);
    boolean know(int uuid);
    String get_name(int uuid);
    boolean debounce(int uuid);
  private:
    _last_times[2] = {0,0};
    _names[2] = {"entree", "porte 3"};
};

#endif
