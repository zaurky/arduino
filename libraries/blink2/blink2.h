#ifndef blink2_h
#define blink2_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define blink_error 5
#define blink_unknown 3
#define blink_ok 1


class Blink2 {
    public:
        Blink2(int led_id, int duration = 1000);
        boolean blink(int times);
        boolean check();
      private:
        int _led_id;
        int _led_state;
        int _duration;
        int _count;
        int _rest;
        int _delta;
        int _active;
        unsigned long _start;
};


class Alive : public Blink2 {
    public:
        Alive(int led_id) : Blink2(led_id) {};
        boolean init();
        boolean check();
};

#endif
