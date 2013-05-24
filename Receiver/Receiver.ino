#include <RCSwitch.h>
#include <blink2.h>
#include <sensor.h>

/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// arduino pin where things are plugged
int msg_id = 2;
int alive_id = 4;
int rc_irq = 0;  // Receiver on inerrupt 0 => that is pin #3 on leonardo


// Objects init
RCSwitch mySwitch = RCSwitch();
Alive alive = Alive(alive_id);
Sensor sensor = Sensor(msg_id);


void setup() {
    mySwitch.enableReceive(rc_irq);
    sensor.init();
    alive.init();
}


void loop() {
    if (mySwitch.available()) {
        sensor.work(mySwitch.getReceivedValue());
        mySwitch.resetAvailable();
    }

    // do checks
    sensor.check();
    alive.check();
}
