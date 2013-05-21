#include "sensor.h"


Sensor::Sensor() {
}


String Sensor::get_name(long sensor_id) {
    switch (sensor_id) {
        case 21817:
            return "entree";
        case 9590072:
            return "test";
        default:
            break;
    }
    return "";
}


boolean Sensor::know(long sensor_id) {
    return get_name(sensor_id).length() != 0;
}
