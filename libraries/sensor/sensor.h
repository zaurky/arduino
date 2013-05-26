#ifndef sensor_h
#define sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <blink2.h>

class Blink2;

#define sensor_door_1 10528568
#define sensor_door_2 5160504
#define sensor_door_3 9590072
#define sensor_door_4 1068344
#define sensor_door_5 16762552
#define sensor_move_1 4273500
#define sensor_move_2 5751900
#define sensor_move_3 3626332
#define key_1_deactivate 3394828

#define debounceDelay 1500

#define sensor_type_door 0
#define sensor_type_zone 1

class Sensor {
    public:
        Sensor(int led_id);
        void init();
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
        unsigned long _last_times[8] = {0,0,0,0,0,0,0,0};
        String _names[8] = {
            "entree", "salon N.E", "salon N.O", "salon O.N", "salon O.S",
            "salon", "zone 2", "zone 3"
        };
        short _sensor_type[8] = {
            sensor_type_door, sensor_type_door, sensor_type_door,
            sensor_type_door, sensor_type_door,
            sensor_type_zone, sensor_type_zone, sensor_type_zone
        };
};

#endif
