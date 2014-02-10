#include <RCSwitch.h>
#include <transmitter.h>


/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// Transmitter params
byte txPin = 12;

Transmitter tx = Transmitter(txPin);


void setup() {
    Serial.begin(9600);
    pinMode(13, OUTPUT);
}


void loop() {
    digitalWrite(13, HIGH);
    tx.send(5393);
    delay(60);
    digitalWrite(13, LOW);
    delay(10000);
}
