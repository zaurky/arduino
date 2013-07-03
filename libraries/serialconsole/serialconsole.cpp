#include "serialconsole.h"


SerialConsole::SerialConsole(Alarm* alarm) {
    _alarm = alarm;
}


void SerialConsole::init_temperature(int tempPin) {
    _tempPin = tempPin;
}

void SerialConsole::init_lumiere(int lumPin) {
    _lumPin = lumPin;
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
    Serial.println("    level : the arm level (1|2|3)");
    Serial.println("  2 : disarm alarm");
    Serial.println("  3 : alarm mute");
    Serial.println("  4 : alarm status");
    if (_tempPin != -1) {
        Serial.println("  7 : show temperature");
    }
    if (_lumPin != -1) {
        Serial.println("  8 : show lumiere");
    }
    Serial.println("");
}


void SerialConsole::arm() {
    Serial.println("REQ: Arming alarm, insert a level please");
    int level = wait_serial();
    while (level < 0 || level > 2) {
        Serial.println("REQ: Arming alarm, insert a level please");
        level = wait_serial();
    }
    _alarm->arm(level);
}


void SerialConsole::disarm() {
    _alarm->disarm();
}


void SerialConsole::mute() {
    _alarm->mute();
}


void SerialConsole::status() {
    if (_alarm->armed()) {
        Serial.print("INFO: The alarm is armed");
        if (_alarm->is_ringing()) {
            Serial.print(" and ringing"); 
        }
        Serial.print(" - level : ");
        Serial.println(_alarm->arm_level());
    } else {
        Serial.println("INFO: The alarm is not armed");
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
            mute();
            break;
        case 4:
            status();
            break;
        case 7:
            Serial.print("INFO: ");
            Serial.print(sensorTemperature(_tempPin));
            Serial.println(" °C");
            break;
        case 8:
            Serial.print("INFO: ");
            Serial.println(analogRead(_lumPin));
            break;
        default:
            help();
    }
    Serial.println("");
}


void SerialConsole::check() {
    action(serial_action());
}
