#ifndef sensor_h
#define sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <blink2.h>
#include <rfid_card.h>

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
#define key_1_deferred 3394819
#define key_1_other 3394864
#define key_2_activate 13972416
#define key_2_deactivate 13972236
#define key_2_deferred 13972227
#define key_2_other 13972272

#define debounceDelay 1500

#define sensor_type_door 0
#define sensor_type_zone 1
#define sensor_type_key_on 2
#define sensor_type_key_off 3
#define sensor_type_key_deferred 4
#define sensor_type_key_other 5
#define sensor_type_rfid_tag 6

#define sensor_nozone 0
#define sensor_zone_1 1
#define sensor_zone_2 2
#define sensor_zone_3 3

#define action_nothing 0
#define action_armed 1
#define action_disarmed 2
#define action_deferred 3
#define action_other 4
#define action_enter 5
#define action_freeze 6

#define delay_immediate 0
#define delay_defered 20000  // 20 secondes
#define delay_freeze 60000  // 60 secondes

class Sensor {
    public:
        Sensor(int led_id);
        void init();
        int work(long sensor_id);
        void check();
        int get_uuid(long sensor_id);
        short type(int uuid);
        short zone(int uuid);
        short delay(int uuid);
        boolean know(int uuid);
        String get_name(int uuid);
        boolean debounce(int uuid);
    private:
        Blink2* _msg_led;

        // all the list that follow must have the same number of elements
        // as sensors uuid declared.
        unsigned long _last_times[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        String _names[19] = {
            "entree", "salon N.O", "salon N.E", "salon E.N", "salon E.S",
            "salon", "escalier", "zone 3",
            "key 1 On", "key 1 Off", "key 1 defered", "key 1 other",
            "key 2 On", "key 2 Off", "key 2 defered", "key 2 other",
            "RFID 1", "RFID 2", "RFID 3"
        };
        short _sensor_type[19] = {
            sensor_type_door, sensor_type_door, sensor_type_door,
            sensor_type_door, sensor_type_door,
            sensor_type_zone, sensor_type_zone, sensor_type_zone,
            sensor_type_key_on, sensor_type_key_off,
            sensor_type_key_deferred, sensor_type_key_other,
            sensor_type_key_on, sensor_type_key_off,
            sensor_type_key_deferred, sensor_type_key_other,
            sensor_type_rfid_tag, sensor_type_rfid_tag, sensor_type_rfid_tag
        };
        short _sensor_zone[19] = {
            sensor_zone_3, sensor_zone_3, sensor_zone_3,
            sensor_zone_3, sensor_zone_3,
            sensor_zone_2, sensor_zone_2, sensor_zone_1,
            sensor_nozone, sensor_nozone, sensor_nozone, sensor_nozone,
            sensor_nozone, sensor_nozone, sensor_nozone, sensor_nozone,
            sensor_nozone, sensor_nozone, sensor_nozone
        };
        short _sensor_delay[19] = {
            delay_defered, delay_immediate, delay_immediate,
            delay_immediate, delay_immediate,
            delay_immediate, delay_immediate, delay_immediate,
            delay_defered, delay_defered, delay_defered, delay_defered,
            delay_defered, delay_defered, delay_defered, delay_defered,
            delay_freeze, delay_freeze, delay_freeze
        };
};

#endif
