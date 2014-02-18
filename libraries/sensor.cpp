#include "sensor.h"


Sensor::Sensor(int led_id) {
    _msg_led = new Blink2(led_id, 1000);
}


void Sensor::init() {
}


int Sensor::work(long sensor_id) {
    int uuid = get_uuid(sensor_id);
    int ret = action_nothing;

    if (!know(uuid)) {
        _msg_led->blink(blink_unknown);
        Serial.print("INFO: Received : ");
        Serial.println(sensor_id);
    } else if (debounce(uuid)) {
        _msg_led->blink(blink_ok);
        if (type(uuid) == sensor_type_door) {
            Serial.print("EVENT: Door opened : ");
            ret = action_enter;
        } else if (type(uuid) == sensor_type_zone) {
            Serial.print("EVENT: Someone in zone : ");
            ret = action_enter;
        } else if (type(uuid) == sensor_type_key_on) {
            Serial.print("EVENT: Key pressed : ");
            ret = action_armed;
        } else if (type(uuid) == sensor_type_key_off) {
            Serial.print("EVENT: Key pressed : ");
            ret = action_disarmed;
        } else if (type(uuid) == sensor_type_key_deferred) {
            Serial.print("EVENT: Key pressed : ");
            ret = action_deferred;
        } else if (type(uuid) == sensor_type_key_other) {
            Serial.print("EVENT: Key pressed : ");
            ret = action_other;
        } else if (type(uuid) == sensor_type_rfid_tag) {
            Serial.print("EVENT: RFID tag detected : ");
            ret = action_freeze;
        }
        Serial.println(get_name(uuid));
    }
    return ret;
}


void Sensor::check() {
    _msg_led->check();
}


int Sensor::get_uuid(long sensor_id) {
    switch (sensor_id) {
        case sensor_door_1:
            return 0;
        case sensor_door_2:
            return 1;
        case sensor_door_3:
            return 2;
        case sensor_door_4:
            return 3;
        case sensor_door_5:
            return 4;
        case sensor_move_1:
            return 5;
        case sensor_move_2:
            return 6;
        case sensor_move_3:
            return 7;
        case key_1_activate:
            return 8;
        case key_1_deactivate:
            return 9;
        case key_1_deferred:
            return 10;
        case key_1_other:
            return 11;
        case key_2_activate:
            return 12;
        case key_2_deactivate:
            return 13;
        case key_2_deferred:
            return 14;
        case key_2_other:
            return 15;
        case sensor_rfid0:
            return 16;
        case sensor_rfid1:
            return 17;
        case sensor_rfid2:
            return 18;
    }
    return -1;
}


short Sensor::zone(int uuid) {
    return _sensor_zone[uuid];
}


short Sensor::delay(int uuid) {
    if (uuid == -1) {
        return 0;
    }
    return _sensor_delay[uuid];
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
