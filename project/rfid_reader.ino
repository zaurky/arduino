#include <rfid_card.h>
#include <rfid.h>


int ack_pin = 2;
Rfid* rfid = new Rfid(ack_pin);


void setup() {
    SPI.begin();
    // Read a fast as possible. There is a limit for how long we are
    // allowed to read from the tags.
    Serial.begin(115200);

    // must be the last one (will take 2sec to init on leonardo board)
    rfid->init();
    rfid->choose_setup(KEYINIT);
}


void loop() {
    long res;

    res = rfid->get_serial();
    if (res != 0) {
        Serial.print("The serial nb of the tag is: ");
        Serial.println(res);
        Card card = Card(res);
        if (card.exists()) {
            Serial.println("This is a known tag");
        }
        rfid->read(4);
    }

    delay(500);
}
