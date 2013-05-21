#ifndef blink_h
#define blink_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

void blink_once(int led_id, int delta, int on=HIGH, int off=LOW);
void blink_more(int led_id, int count, int delta, int on=HIGH, int off=LOW);

class Blink {
  public:
    Blink(int led_id, int duration = 1000, int rest = 500);
    void blink(int times);
  private:
    int _led_id;
    int _duration;
    int _rest;
};

#endif
