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


class Alarm {
    public:
        Alarm(int rc_irq, int sensor_led_id, int armed_id);
        void init(int rc_irq = 0);
        int work(long sensor_id);
        void check();
    protected:
        RCSwitch* mySwitch;
    private:
        Sensor* _sensor;
        Led* _armed_led;
};

#endif
