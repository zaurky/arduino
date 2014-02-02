#include <RCSwitch.h>
#include <transmitter.h>


/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// Transmitter params
int txPin = 12;

Transmitter tx = Transmitter(txPin);


void setup() {
    Serial.begin(9600);
}


void loop() {
    tx.check();
}
