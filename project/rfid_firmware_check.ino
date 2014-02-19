#include <rfid.h>


int ack_pin = 2;
Rfid* rfid = new Rfid(ack_pin);


void setup() {
    SPI.begin();
    Serial.begin(115200);

    rfid->init();
    rfid->choose_setup(KEYINIT);
    rfid->self_test();
}


void loop() {
    delay(1000000);
}
