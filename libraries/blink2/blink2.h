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


class Led {
    public:
        Led(int led_id);
        void on();
        void off();
        int state;
    private:
        int _led_id;
};


class Blink2 {
    public:
        Blink2(int led_id, int duration = 1000);
        boolean blink(int times);
        boolean check();
      private:
        Led* _led;
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
        void order(char* command);
};


class LedInit {
    public:
        LedInit(int* leds, int len, int delta_a=100, int delta_b=500);
        void init();
    private:
        int _len;
        int* _leds;
        int _delta_a;
        int _delta_b;
};

#endif
