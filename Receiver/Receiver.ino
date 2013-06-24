#include <RCSwitch.h>
#include <blink2.h>
#include <sensor.h>
#include <buzzer.h>
#include <alarm.h>
#include <serialconsole.h>
#include <utils.h>


/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/


// Alarm instanciation with led on pin 2, 4 and 5
int tempPin = 0;
int lumPin = 1;

Alarm alarm = Alarm(2, 4, 5, 13);
SerialConsole serial_console = SerialConsole(&alarm);


void setup() {
    Serial.begin(9600);

    // Receiver on inerrupt 0 => that is pin #3 on leonardo
    alarm.init(0);
    alarm.arm(2);

    serial_console.init_temperature(tempPin);
    serial_console.init_lumiere(lumPin);
}


void loop() {
    // if something comes from the serial
    serial_console.check();

    // do checks
    alarm.check();
}
