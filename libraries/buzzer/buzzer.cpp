#include "Arduino.h"
#include "buzzer.h"


Buzzer::Buzzer(int buzzer_id) {
    _buzzer_id = buzzer_id;
    _duration = 0;
    _start = 0;
}


void Buzzer::on(int duration) {
    _duration = duration;
    digitalWrite(_buzzer_id, HIGH);
}


void Buzzer::off() {
    digitalWrite(_buzzer_id, LOW);
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
