#include "sensor.h"


Sensor::Sensor(int led_id) {
    _msg_led = new Blink2(led_id, 1000);
}


void Sensor::work(long sensor_id) {
    int uuid = get_uuid(sensor_id);

    if (!know(uuid)) {
        _msg_led->blink(blink_unknown);
        Serial.print("Received : ");
        Serial.println(sensor_id);
    } else if (debounce(uuid)) {
        _msg_led->blink(blink_ok);
        if type(uuid) == sensor_type_door:
            Serial.print("Door opened : ");
        else if type(uuid) == sensor_type_zone:
            Serial.print("Someone in zone : ");
        Serial.println(get_name(uuid));
    }
}


void Sensor::check() {
    _msg_led->check();
}


int Sensor::get_uuid(long sensor_id) {
    switch (sensor_id) {
        case sensor_door_1:
            return 0;
        case sensor_door_4:
            return 1;
        case sensor_move_1:
            return 2;
    }
    return -1;
}


boolean Sensor::know(int uuid) {
    return uuid != -1;
}


short Sensor::type(int uuid) {
    return _sensor_type[uuid];
}


String Sensor::get_name(int uuid) {
    if (!know(uuid)) {return "";}
    return _names[uuid];
}


boolean Sensor::debounce(int uuid) {
    if ((_last_times[uuid] == 0) || ((millis() - _last_times[uuid]) > debounceDelay)) {
        _last_times[uuid] = millis();
        return true;
    }
    return false;
}
