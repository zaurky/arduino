#include "Arduino.h"
#include "transmitter.h"


Transmitter::Transmitter(byte txPin) : _tx_id(txPin) {
    mySwitch = new RCSwitch();
    mySwitch->enableTransmit(_tx_id);
    mySwitch->setRepeatTransmit(TXREPEAT);

    pinMode(13, OUTPUT);
}


void Transmitter::check() {
    digitalWrite(13, HIGH);
    mySwitch->send(5393, 24);
    delay(60);
    digitalWrite(13, LOW);

    delay(10000);
}

