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
    _delta = _duration / (2 * times);
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


/**
 * Alive object : blink a led (led_id) every second.
 */
boolean Alive::init() {
    blink(5);
}


boolean Alive::check() {
    if (Blink2::check()) {
        blink(1);
    }
}


void Alive::order(char* command) {
    Serial.println(command);
}


/**
 * LedInit object : show that all leds work
 */
LedInit::LedInit(int* leds, int len, int delta_a, int delta_b) {
    _len = len;
    _leds = leds;
    _delta_a = delta_a;
    _delta_b = delta_b;
}


void LedInit::init() {
    for (int id = 0; id < _len; id ++) {
        pinMode(_leds[id], OUTPUT);
        digitalWrite(_leds[id], HIGH);
        delay(_delta_a);
    }
    delay(_delta_b);
    for (int id = 0; id < _len; id ++) {
        digitalWrite(_leds[id], LOW);
        delay(_delta_a);
    }
}
