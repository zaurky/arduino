#ifndef serial_console_h
#define serial_console_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <utils.h>
#include <alarm.h>


class SerialConsole {
    public:
        SerialConsole(Alarm* alarm);
        void init_temperature(int tempPin);
        void init_lumiere(int lumPin);
        int serial_action();
        int wait_serial();
        void help();
        void arm();
        void disarm();
        void mute();
        void status();
        void action(int action_id);
        void check();
    private:
        Alarm* _alarm;
        int _tempPin = -1;
        int _lumPin = -1;
};

#endif
