#include "Arduino.h"
#include "buzzer.h"


Buzzer::Buzzer(int buzzer_id) {
    _buzzer_id = buzzer_id;
    _duration = 0;
    _start = 0;

    _state = LOW;
    pinMode(_buzzer_id, OUTPUT);
    digitalWrite(_buzzer_id, _state);
}


void Buzzer::on(int duration) {
    _duration = duration;
    _state = HIGH;
    digitalWrite(_buzzer_id, _state);
}


void Buzzer::off() {
    _state = LOW;
    digitalWrite(_buzzer_id, _state);
}


void Buzzer::check() {
    if (_start == 0 || _duration == -1) {
        return;
    }

    if (millis() - _start > _duration) {
        _start = 0;
        _duration = 0;
        off();
    }
}


bool Buzzer::is_on() {return _state == HIGH;}
