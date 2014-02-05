#include "Arduino.h"
#include "blink.h"

// blink an LED once
void blink_once(int led_id, int delta, int on, int off) {
    digitalWrite(led_id, on);
    delay(delta/2);
    digitalWrite(led_id, off);
    delay(delta/2);
}


// blink an LED the number of times given in the count parameter
void blink_more(int led_id, int count, int delta, int on, int off) {
    while (count > 0) {
        blink_once(led_id, delta, on, off);
        count--;
    }
}


// 
Blink::Blink(int led_id, int duration, int rest) {
    pinMode(led_id, OUTPUT);
    _led_id = led_id;
    _duration = duration;
    _rest = rest;
}

void Blink::blink(int times) {
    int delta = _duration / times;
    blink_more(_led_id, times, delta);
    delay(_rest);
}
