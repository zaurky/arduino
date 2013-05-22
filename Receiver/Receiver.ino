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
int blink_error = 5;
int blink_unknown = 3;
int blink_ok = 1;


RCSwitch mySwitch = RCSwitch();
Blink2 msg_led = Blink2(msg_id);
Blink2 alive = Blink2(alive_id);
Sensor sensor = Sensor();


void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #3 on leonardo
  alive.blink(5);  // blink 5 times at startup
}

void loop() {
  if (mySwitch.available()) {
    long value = mySwitch.getReceivedValue();
    int uuid = sensor.get_uuid(value);

    if (!sensor.know(uuid)) {
      msg_led.blink(blink_unknown);
      Serial.print("Received : ");
      Serial.println(value);
    } else if (sensor.debounce(uui)) {
      msg_led.blink(blink_ok);
      Serial.print("Door opened : ");
      Serial.println(sensor.get_name(uuid));
    }
    mySwitch.resetAvailable();
  }

  msg_led.check();

  if (alive.check()) {
    alive.blink(2);
  }
}
