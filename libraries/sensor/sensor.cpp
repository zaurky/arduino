#include "sensor.h"


Sensor::Sensor() {
}


String Sensor::get_name(long sensor_id) {
    switch (sensor_id) {
        case sensor_door_1:
            return "entree";
        case sensor_door_4:
            return "test";
    }
    return "";
}


boolean Sensor::know(long sensor_id) {
    return get_name(sensor_id).length() != 0;
}
