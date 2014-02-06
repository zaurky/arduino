#ifndef transmitter_h
#define transmitter_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <RCSwitch.h>

#define TXREPEAT 15


class Transmitter {
    public:
        Transmitter(byte txPin);
        void check();
    protected:
        RCSwitch* mySwitch;
    private:
        byte _tx_id;
};

#endif
