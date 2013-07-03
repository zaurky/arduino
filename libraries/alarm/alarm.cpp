#include "Arduino.h"
#include "alarm.h"


Alarm::Alarm(int alive_id, int sensor_led_id, int armed_id, int buzzer_id) {
    mySwitch = new RCSwitch();
    _sensor = new Sensor(sensor_led_id);
    _armed_led = new Led(armed_id);
    _alive = new Alive(alive_id);
    _leds = new int[3]{alive_id, sensor_led_id, armed_id};
    _buzzer = new Buzzer(buzzer_id);
}


void Alarm::init(int rc_irq) {
    LedInit init = LedInit(_leds, 3);
    init.init();

    mySwitch->enableReceive(rc_irq);
    _alive->init();
    _sensor->init();
}


int Alarm::work(long sensor_id) {
    int uuid = _sensor->get_uuid(sensor_id);
    int action = _sensor->work(sensor_id);

    if (action == action_armed) {
        arm();
    } else if (action == action_disarmed) {
        disarm();
    } else if (action == action_defeared) {
        defeared();
    } else if (action == action_other) { // only arm outside doors
        arm(2);
    } else if (action == action_enter) {
        if (_sensor->zone(uuid) >= _arm_level) {
            door_open();
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

    // handle defeared arm
    if (_defeared != 0) {defeared_arm();}

    // handle defeared ring
    if (_ring != 0) {door_open_ring();}

    _alive->check();
    _sensor->check();
}


// alarm disarm
void Alarm::disarm() {
    Serial.println("INFO: Alarm disarmed");
    _armed_led->off();
    _buzzer->off();
    _defeared = 0;
    _ring = 0;
    _arm_level = 1000;
}


// alarm arm
void Alarm::defeared_arm() {
    if (millis() - _defeared >= defeardedDelay) {arm();}
}


void Alarm::arm(int level) {
    Serial.print("INFO: Alarm armed at level ");
    Serial.println(level);
    _armed_led->on();
    _defeared = 0;
    _arm_level = level;
}


void Alarm::defeared() {_defeared = millis();}


// is alarm armed ?
boolean Alarm::armed() {return _armed_led->state == HIGH;}


short Alarm::arm_level() {return _arm_level;}


// alarm fired
void Alarm::door_open_ring() {
    if (millis() - _ring >= ringDelay) {ring();}
}


void Alarm::door_open() {
    if (_ring == 0) {
        _ring = millis();
    }
}


void Alarm::mute() {
    if (_buzzer->is_on()) {
        Serial.println("INFO: Alarm muted");
        _buzzer->off();
        _ring = 0;
    } else {
        Serial.println("INFO: Alarm does not need mute");
    }
}


void Alarm::ring() {
    Serial.println("ALARM: Alarm ring!");
    _buzzer->on();
    _ring = 0;
}


boolean Alarm::is_ringing() {
    return _buzzer->is_on();
}
