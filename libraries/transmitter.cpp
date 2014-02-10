#include "Arduino.h"
#include "transmitter.h"


Transmitter::Transmitter(byte txPin) : _tx_id(txPin) {
    mySwitch = new RCSwitch();
    mySwitch->enableTransmit(_tx_id);
    mySwitch->setRepeatTransmit(TXREPEAT);
}


void Transmitter::send(int code) {
    mySwitch->send(code, 24);
}
