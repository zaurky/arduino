#include "sensor.h"


Sensor::Sensor() {
}


int Sensor::get_uuid(long sensor_id) {
    switch (sensor_id) {
        case sensor_door_1:
            return 0;
        case sensor_door_4:
            return 1;
    }
    return -1;
}


boolean Sensor::know(int uuid) {
    return uuid != -1;
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
