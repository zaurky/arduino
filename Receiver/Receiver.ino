#include <alarm.h>

/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// Objects instanciation
Alarm alarm = Alarm(2, 4, 5);


void setup() {
    // Receiver on inerrupt 0 => that is pin #3 on leonardo
    alarm.init(0);
}


void loop() {
    // if something comes from the serial
    /*if (Serial.available() > 0) {
        char serInString[50];
        readSerialString(serInString);
        alive.order(serInString);
    }*/

    // do checks
    alarm.check();
}
