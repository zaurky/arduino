#include <blink2.h>

boolean done[] = {true, true, true};
Blink2 blink[] = {Blink2(2, 1000), Blink2(3, 2000), Blink2(4, 3000)};

void setup() {
    Serial.begin(9600);
}

void loop() {
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
