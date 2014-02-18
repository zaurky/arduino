#ifndef rfid_h
#define rfid_h

#include <MFRC522.h>
#include <SPI.h>
#include <blink2.h>
#include <rfid_card.h>


#define SAD 10
#define RST 5


#define KEYINIT 0
#define KEYMINE 1


#define DEBUG


class Rfid {
    public:
        Rfid(int ack_pin);
        bool init();
        bool self_test();
        void choose_setup(short setup);
        bool read_block(int i, byte* data);
        void print_block(int i, byte* data);
        bool get_tag(byte* data, byte* serial);
        void release_tag(bool success);
        void print_tag(byte* data, byte* serial);
        bool auth_and_read(byte mode, byte block, byte *key, byte *serial, byte* data, bool print);
        void read(short nb_block);
        long get_serial();
    protected:
        byte key_init[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
        byte key_mine[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
    private:
        MFRC522* _nfc;
        Led* _ack_led;
        byte _is_init = 0;
        byte _mode;
        byte* _key;
};


#endif
