#include "serialconsole.h"


SerialConsole::SerialConsole(Alarm* alarm) {
    _alarm = alarm;
}


int SerialConsole::serial_action() {
    if (Serial.available() > 0) {
        return readSerialInt();
    }
    return -1;
}


int SerialConsole::wait_serial() {
    while (Serial.available() == 0) {
        delay(10);
    }
    return serial_action();
}


void SerialConsole::help() {
    Serial.println("");
    Serial.println("serial console for alarm");
    Serial.println("commands :");
    Serial.println("  0 : help");
    Serial.println("  1 : arm alarm");
    Serial.println("    level : the arm level (0|1|2)");
    Serial.println("  2 : disarm alarm");
    Serial.println("  3 : alarm status");
    Serial.println("");
}


void SerialConsole::arm() {
    Serial.println("Arming alarm, insert a level please");
    _alarm->arm(wait_serial());
}


void SerialConsole::disarm() {
    _alarm->disarm();
}


void SerialConsole::status() {
    if (_alarm->armed()) {
        Serial.print("The alarm is armed - level : ");
        Serial.println(_alarm->arm_level());
    } else {
        Serial.println("The alarm is not armed");
    }
}


void SerialConsole::action(int action_id) {
    switch (action_id) {
        case -1:
            return;
        case 0:
            help();
            break;
        case 1:
            arm();
            break;
        case 2:
            disarm();
            break;
        case 3:
            status();
            break;
        default:
            help();
    }
    Serial.println("");
}


void SerialConsole::check() {
    action(serial_action());
}
