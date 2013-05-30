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
        int serial_action();
        int wait_serial();
        void help();
        void arm();
        void disarm();
        void action(int action_id);
        void check();
    private:
        Alarm* _alarm;
};

#endif
