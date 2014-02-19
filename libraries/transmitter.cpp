#include "Arduino.h"
#include "transmitter.h"


Transmitter::Transmitter(byte txPin) : _tx_id(txPin) {
    _mySwitch = new RCSwitch();
    _mySwitch->enableTransmit(_tx_id);
    _mySwitch->setRepeatTransmit(TXREPEAT);
}


void Transmitter::send(int code) {
    _mySwitch->send(code, 24);
}
