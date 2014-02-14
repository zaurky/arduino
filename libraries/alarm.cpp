#include "Arduino.h"
#include "alarm.h"


Alarm::Alarm(int alive_id, int sensor_led_id, int *armed_id, int buzzer_id) {
    mySwitch = new RCSwitch();
    _sensor = new Sensor(sensor_led_id);
    _armed_led = new Leds(armed_id, 3);
    _alive = new Alive(alive_id);
    _leds = new int[5]{alive_id, sensor_led_id,
                       armed_id[0], armed_id[1], armed_id[2]};
    _buzzer = new Buzzer(buzzer_id);
}


void Alarm::init(int rc_irq) {
    LedInit init = LedInit(_leds, 5);
    init.init();

    mySwitch->enableReceive(rc_irq);
    _alive->init();
    _sensor->init();
}


int Alarm::work(long sensor_id) {
    int uuid = _sensor->get_uuid(sensor_id);
    int action = _sensor->work(sensor_id);

    if (action == action_armed) {
        arm(1);
    } else if (action == action_disarmed) {
        disarm();
    } else if (action == action_deferred) {
        deferred();
    } else if (action == action_other) { // only arm outside doors
        arm(2);
    } else if (action == action_enter) {
        if (_sensor->zone(uuid) >= _arm_level) {
            raise();
        }
    }
    return action;
}


void Alarm::check() {
    // if something comes from the RF sensor
    if (mySwitch->available()) {
        work(mySwitch->getReceivedValue());
        mySwitch->resetAvailable();
    }

    // handle deferred arm
    if (_deferred != 0) {deferred_arm();}

    // handle deferred ring
    if (_raised != 0) {deferred_ring();}

    _alive->check();
    _sensor->check();
}


// alarm disarm
void Alarm::disarm() {
    Serial.println("INFO: Alarm disarmed");
    _armed_led->off();
    _buzzer->off();
    _deferred = 0;
    _raised = 0;
    _arm_level = 1000;
}


// alarm deferred arm
void Alarm::deferred_arm() {
    if (millis() - _deferred >= defeardedDelay) {arm();}
}


void Alarm::arm(int level) {
    Serial.print("INFO: Alarm armed at level ");
    Serial.println(level);
    _armed_led->on(level);
    _deferred = 0;
    _arm_level = level;
}


void Alarm::deferred() {_deferred = millis();}


// is alarm armed ?
boolean Alarm::armed() {return _arm_level > 0;}


short Alarm::arm_level() {return _arm_level;}


// alarm fired
void Alarm::deferred_ring() {
    if (millis() - _raised >= ringDelay) {
        ring();
    }
}


void Alarm::raise() {
    if (_raised == 0) {
        _raised = millis();
    }
}


void Alarm::mute() {
    if (_buzzer->is_on()) {
        Serial.println("INFO: Alarm muted");
        _buzzer->off();
        _raised = 0;
    } else {
        Serial.println("INFO: Alarm does not need mute");
    }
}


void Alarm::ring() {
    Serial.println("ALARM: Alarm ring!");
    _buzzer->on();
    _raised = 0;
}


boolean Alarm::is_ringing() {
    return _buzzer->is_on();
}
