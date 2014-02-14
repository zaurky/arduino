#ifndef alarm_h
#define alarm_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <blink2.h>
#include <sensor.h>
#include <buzzer.h>
#include <RCSwitch.h>


#define defeardedDelay 30000
#define bipDelay 30000
#define ringDelay 60000


class Alarm {
    public:
        Alarm(int alive_id, int sensor_led_id, int *armed_id, int buzzer_id);
        void init(int rc_irq = 0);
        int work(long sensor_id);
        void check();
        void arm(int level = 0);
        void disarm();
        void defeared_arm();
        void defeared();
        boolean armed();
        short arm_level();
        void mute();
        void ring();
        boolean is_ringing();
        void raise();
        void defeared_ring();
    protected:
        RCSwitch* mySwitch;
    private:
        Sensor* _sensor;
        Leds* _armed_led;
        Alive* _alive;
        Buzzer* _buzzer;
        unsigned long _defeared = 0;
        unsigned long _raised = 0;
        int* _leds;
        short _arm_level = 0;
};

#endif
