#ifndef sensor_h
#define sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <blink2.h>

class Blink2;

#define sensor_door_1 21816
#define sensor_door_4 9590072
#define sensor_move_1 4273500

#define debounceDelay 1500

#define sensor_type_door 0
#define sensor_type_zone 1

class Sensor {
    public:
        Sensor(int led_id);
        void work(long sensor_id);
        void check();
        int get_uuid(long sensor_id);
        short type(int uuid);
        boolean know(int uuid);
        String get_name(int uuid);
        boolean debounce(int uuid);
    private:
        Blink2* _msg_led;

        // all the list that follow must have the same number of elements
        // as sensors uuid declared.
        unsigned long _last_times[3] = {0,0,0};
        String _names[3] = {"entree", "salon N.O", "salon"};
        short _sensor_type[3] = {sensor_type_door, sensor_type_door, sensor_type_zone};
};

#endif
