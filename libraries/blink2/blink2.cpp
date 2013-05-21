#include "Arduino.h"
#include "blink2.h"


Blink2::Blink2(int led_id, int duration) {
    _active = false;
    _led_id = led_id; 
    _led_state = LOW;
    _duration = duration;
    _delta = 0;
    pinMode(_led_id, OUTPUT);
    digitalWrite(_led_id, _led_state);
}   


boolean Blink2::blink(int times) {
    if (_active) {
        return false;
    }
    _active = true;
    _start = millis();
    _count = times;
    _delta = _duration / times;
    return true;
}


boolean Blink2::check() {
    if (!_active) {
        return false;
    }
    unsigned long currentMillis = millis();
 
    if (currentMillis - _start >= _delta) {
        // save the last time you blinked the LED
        _start = currentMillis;  

        // if the LED is off turn it on and vice-versa:
        if (_led_state == LOW) {
            _led_state = HIGH;
        } else {
            _led_state = LOW;
    	    _count--;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(_led_id, _led_state);

        if (_count == 0) {
            _active = false;
            return true;
        }
    }
    return false;
}
