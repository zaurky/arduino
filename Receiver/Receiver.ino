#include <RCSwitch.h>
#include <blink2.h>
#include <sensor.h>

/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// arduino pin where things are plugged (need at least 3 leds)
int leds[3] = {2, 4, 5};

// Receiver on inerrupt 0 => that is pin #3 on leonardo
int rc_irq = 0;


// Objects instanciation
RCSwitch mySwitch = RCSwitch();
Alive alive = Alive(leds[0]);
Sensor sensor = Sensor(leds[1], leds[2]);


void setup() {
    LedInit init = LedInit(leds, 3);

    mySwitch.enableReceive(rc_irq);
    init.init();
    sensor.init();
    alive.init();
}


void loop() {
    // if something comes from the RF sensor
    if (mySwitch.available()) {
        sensor.work(mySwitch.getReceivedValue());
        mySwitch.resetAvailable();
    }

    // if something comes from the serial
    /*if (Serial.available() > 0) {
        char serInString[50];
        readSerialString(serInString);
        alive.order(serInString);
    }*/

    // do checks
    sensor.check();
    alive.check();

    // wait between loops
    delay(10);
}
