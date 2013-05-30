#include "serialconsole.h"


SerialConsole::SerialConsole(Alarm* alarm) {
    _alarm = alarm;
}


int SerialConsole::serial_action() {
    int action = -1;
    if (Serial.available() > 0) {
        Serial.println("got data");
        action = readSerialInt();
        Serial.println(action);
    }
    return action;
}


int SerialConsole::wait_serial() {
    while (Serial.available() == 0) {
        delay(10);
    }
    return serial_action();
}


void SerialConsole::help() {
    Serial.println("serial console for alarm");
    Serial.println("commands :");
    Serial.println("  0 : help");
    Serial.println("  1 : arm alarm");
    Serial.println("    level : the arm level (0|1|2)");
    Serial.println("  2 : disarm alarm");
}


void SerialConsole::arm() {
    Serial.println("insert level please");
    int level = wait_serial();
    _alarm->arm(level);
}


void SerialConsole::disarm() {
    _alarm->disarm();
}


void SerialConsole::action(int action_id) {
    switch (action_id) {
        case -1:
            break;
        case 0:
            help();
            break;
        case 1:
            arm();
            break;
        case 2:
            disarm();
            break;
        default:
            help();
    }
}


void SerialConsole::check() {
    action(serial_action());
}
