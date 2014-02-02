#include "Arduino.h"
#include "buzzer.h"


/*
boolean seq[10] = {true, true, true, false, false, false, true, false, true, false};
sequence(inputPin, seq, 9);
*/

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


void Buzzer::play_sequence(boolean* seq, int len) {
    for (int i = 0; i < len; i++) {
        if (seq[i]) {
            analogWrite(_buzzer_id, 1000);
        } else {
            analogWrite(_buzzer_id, 0);
        }
    }
}
