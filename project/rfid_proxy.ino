#include <RCSwitch.h>
#include <transmitter.h>
#include <rfid_card.h>
#include <rfid.h>


/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// Transmitter params
byte tx_pin = 12;
byte ack_pin = 2;

Transmitter tx = Transmitter(tx_pin);
Rfid rfid = Rfid(ack_pin);


void setup() {
    SPI.begin();
    // Read a fast as possible. There is a limit for how long we are
    // allowed to read from the tags.
    Serial.begin(115200);

    // must be the last one (will take 2sec to init on leonardo board)
    rfid.init();
    rfid.choose_setup(KEYINIT);
}


void loop() {
    long res;

    res = rfid.get_serial();
    if (res != 0) {
        Card card = Card(res);
        if (card.exists()) {
            Serial.println("Tag was detected");
            tx.send(card.get_message());
        }
    }

    delay(500);
}
