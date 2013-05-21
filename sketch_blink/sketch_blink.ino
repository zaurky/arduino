#include <blink2.h>

boolean done[] = {true, true, true};
Blink2 blink[] = {Blink2(2, 1000, 0), Blink2(3, 1000, 0), Blink2(4, 1000, 0)};

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (!Serial);
  for (int index = 0; index < 3; index++) {
    if (done[index]) {
      Serial.print("reinit : ");
      Serial.println(index);
      blink[index].blink(5*(index+1));
    }
    done[index] = blink[index].check();
  }
  delay(10);
}
