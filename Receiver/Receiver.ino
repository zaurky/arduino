#include <RCSwitch.h>
#include <blink2.h>
#include <sensor.h>


int msg_id = 2;
int alive_id = 4;
int msg_active = false;
int blink_error = 5;
int blink_unknown = 3;
int blink_ok = 1;


RCSwitch mySwitch = RCSwitch();
Blink2 msg_led = Blink2(msg_id);
Blink2 alive = Blink2(alive_id);
Sensor sensor = Sensor();


void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
  alive.blink(5);
}

void loop() {
  if (mySwitch.available()) {
    long value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.print("Unknown encoding");
      msg_led.blink(blink_error);
      msg_active = true;
    } else {
      if (!sensor.know(value)) {
        msg_led.blink(blink_unknown);
        Serial.print("Received ");
        Serial.println(value);
      } else {
        msg_led.blink(blink_ok);
        Serial.print("Door opened : ");
        Serial.println(sensor.get_name(value));
      }

      msg_active = true;
    }
    mySwitch.resetAvailable();
  }

  if (msg_active && msg_led.check()) {
      msg_active = false;
  }

  if (alive.check()) {
    alive.blink(2);
  }
}
