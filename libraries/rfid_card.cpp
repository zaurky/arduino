#include "rfid_card.h"


Card::Card(long code) : _code(code) {}


bool Card::exists() {
    switch (_code) {
        case sensor_rfid0:
            return true;
        case sensor_rfid1:
            return true;
        case sensor_rfid2:
            return true;
    }
    return false;
}


long Card::get_message() {
    return _code;
}
