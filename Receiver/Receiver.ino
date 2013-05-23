#include <RCSwitch.h>
#include <blink2.h>
#include <sensor.h>

/*
This code is done for Leonardo arduino board, if you plan to use it somewhere else,
pay attention to the size of int and long. Here value goes in a long, because we
get 32 bits values.
*/

int msg_id = 2;
int alive_id = 4;


RCSwitch mySwitch = RCSwitch();
Blink2 alive = Blink2(alive_id);
Sensor sensor = Sensor(msg_id);


void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #3 on leonardo
  alive.blink(5);  // blink 5 times at startup
}

void loop() {
  if (mySwitch.available()) {
    long value = mySwitch.getReceivedValue();
    sensor.work(value);
    mySwitch.resetAvailable();
  }

  sensor.check();

  if (alive.check()) {
    alive.blink(2);
  }
}
