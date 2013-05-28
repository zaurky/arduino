#include <RCSwitch.h>
#include "alarm.h"


Alarm::Alarm(int sensor_led_id, int armed_id) {
    mySwitch = new RCSwitch();
    _sensor = new Sensor(sensor_led_id);
    _armed_led = new Led(armed_id);
}


void Alarm::init(int rc_irq) {
    mySwitch->enableReceive(rc_irq);
    _sensor->init();
}


int Alarm::work(long sensor_id) {
    int uuid = get_uuid(sensor_id);
    int action = _sensor->work(sensor_id);

    if (action == action_armed) {
        _armed_led->on();
    } else if (action == action_desarmed) {
        _armed_led->off();
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

    _sensor->check();
}
