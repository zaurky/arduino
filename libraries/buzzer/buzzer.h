#ifndef buzzer_h
#define buzzer_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif


class Buzzer {
  public:
    Buzzer(int buzzer_id);
    void on(int duration = -1);
    void off();
    void check();
    bool is_on();
    void play_sequence(boolean* seq, int len);
  private:
    int _buzzer_id;
    int _duration;
    int _state;
    unsigned long _start;
};

#endif
