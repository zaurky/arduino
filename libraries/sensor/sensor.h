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

#define sensor_door_6 14484816

#define sensor_move_1 4273500
#define sensor_move_2 5751900
#define sensor_move_3 3626332
#define key_1_activate 3395008
#define key_1_deactivate 3394828
#define key_1_defeared 3394819
#define key_1_other 1111 // put the right code
#define key_2_activate 13972416
#define key_2_deactivate 13972236
#define key_2_defeared 13972227
#define key_2_other 13972272

#define debounceDelay 1500
#define dereadedDealay 30000

#define sensor_type_door 0
#define sensor_type_zone 1
#define sensor_type_key_on 2
#define sensor_type_key_off 3
#define sensor_type_key_defeared 4
#define sensor_type_key_other 5


class Sensor {
    public:
        Sensor(int led_id, int armed_id);
        void init();
        int work(long sensor_id);
        void check();
        int get_uuid(long sensor_id);
        short type(int uuid);
        boolean know(int uuid);
        String get_name(int uuid);
        boolean debounce(int uuid);
    private:
        Blink2* _msg_led;
        Led* _armed_led;

        // all the list that follow must have the same number of elements
        // as sensors uuid declared.
        unsigned long _last_times[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        String _names[16] = {
            "entree", "salon N.O", "salon N.E", "salon E.N", "salon E.S",
            "salon", "zone 2", "zone 3",
            "key 1 On", "key 1 Off", "key 1 defered", "key 1 other",
            "key 2 On", "key 2 Off", "key 2 defered", "key 2 other"
        };
        short _sensor_type[16] = {
            sensor_type_door, sensor_type_door, sensor_type_door,
            sensor_type_door, sensor_type_door,
            sensor_type_zone, sensor_type_zone, sensor_type_zone,
            sensor_type_key_on, sensor_type_key_off, sensor_type_key_defeared,
            sensor_type_key_other, sensor_type_key_on, sensor_type_key_off,
            sensor_type_key_defeared, sensor_type_key_other
        };
};

#endif
