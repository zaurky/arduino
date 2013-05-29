#ifndef alarm_h
#define alarm_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <blink2.h>
#include <sensor.h>
#include <RCSwitch.h>


#define defeardedDelay 30000
#define bipDelay 30000
#define ringDelay 60000


class Alarm {
    public:
        Alarm(int alive_id, int sensor_led_id, int armed_id);
        void init(int rc_irq = 0);
        int work(long sensor_id);
        void check();
        void arm();
        void desarm();
        void defeared_arm();
        void defeared();
        boolean armed();
        void ring();
        void door_open();
        void door_open_ring();
    protected:
        RCSwitch* mySwitch;
    private:
        Sensor* _sensor;
        Led* _armed_led;
        Alive* _alive;
        unsigned long _defeared = 0;
        unsigned long _ring = 0;
        int* _leds;
};

#endif
