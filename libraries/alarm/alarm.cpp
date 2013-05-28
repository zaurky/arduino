#include "alarm.h"


Alarm::Alarm(int alive_id, int sensor_led_id, int armed_id) {
    mySwitch = new RCSwitch();
    _sensor = new Sensor(sensor_led_id);
    _armed_led = new Led(armed_id);
    _alive = new Alive(alive_id);
    _leds = {alive_id, sensor_led_id, armed_id};
}


void Alarm::init(int rc_irq) {
    LedInit init = LedInit(_leds, 3);
    init.init();

    mySwitch->enableReceive(rc_irq);
    _alive->init();
    _sensor->init();
}


int Alarm::work(long sensor_id) {
    int uuid = get_uuid(sensor_id);
    int action = _sensor->work(sensor_id);

    if (action == action_armed) {
        arm();
    } else if (action == action_desarmed) {
        desarm();
    } else if (action == action_defeared) {
        // do somethink in delay
        // _armed_led->off();
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
    if (_defeared != 0) {
        defeared_arm();
    }

    _alive->check();
    _sensor->check();
}


void Alarm::arm() {_armed_led->on();}


void Alarm::desarm() {_armed_led->off();}


void Alarm::defeared_arm() {
    unsigned long currentMillis = millis();

    if (currentMillis - _defeared >= defeardedDelay) {
        arm();
        _defeared = 0;
    }
}


void Alarm::defeared() {_defeared = currentMillis = millis();}


boolean Alarm::armed() {return _armed_led->state == HIGH;}
