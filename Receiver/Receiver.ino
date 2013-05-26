#include <RCSwitch.h>
#include <blink2.h>
#include <sensor.h>

/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// arduino pin where things are plugged
int leds[3] = {2, 4, 5};
int msg_id = leds[1];
int alive_id = leds[0];
int rc_irq = 0;  // Receiver on inerrupt 0 => that is pin #3 on leonardo


// Objects init
RCSwitch mySwitch = RCSwitch();
Alive alive = Alive(alive_id);
Sensor sensor = Sensor(msg_id);


void setup() {
    mySwitch.enableReceive(rc_irq);
    LedInit init = LedInit(leds, 3);
    init.init();
    sensor.init();
    alive.init();
}


void readSerialString(char* serInString) {
    int sb;
    int serInIndx = 0;
    if (Serial.available()) {
        while (Serial.available()){
            sb = Serial.read();
            serInString[serInIndx] = sb;
            serInIndx++;
        }
    }
}


void loop() {
    // if something comes from the RF sensor
    if (mySwitch.available()) {
        sensor.work(mySwitch.getReceivedValue());
        mySwitch.resetAvailable();
    }

    // if something comes from the serial
    if (Serial.available() > 0) {
        char serInString[50];
        readSerialString(serInString);
        alive.order(serInString);
    }

    // do checks
    sensor.check();
    alive.check();

    // wait between loops
    delay(100);
}
