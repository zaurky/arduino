#ifndef transmitter_h
#define transmitter_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <RCSwitch.h>


class Transmitter {
    public:
        Transmitter(int txPin);
        void check();
    protected:
        RCSwitch* mySwitch;
    private:
        int _tx_id;
};

#endif
