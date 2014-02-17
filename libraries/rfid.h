#ifndef rfid_h
#define rfid_h

#include <MFRC522.h>
#include <SPI.h>
#include <blink2.h>


#define tag0 0xa306408b // [A3, 6, 40, 8B]
#define tag1 0x93367f81 // [93, 36, 7F, 81]
#define tag2 0x8e49dc84 // [8E, 49, DC, 84]


#define SAD 10
#define RST 5


#define KEYINIT 0
#define KEYMINE 1


#define DEBUG


class Rfid {
    public:
        Rfid(int ack_pin);
        bool init();
        void choose_setup(short setup);
        bool read_block(int i, byte* data);
        void print_block(int i, byte* data);
        bool get_tag(byte* data, byte* serial);
        void release_tag(bool success);
        void print_tag(byte* data, byte* serial);
        bool auth_and_read(byte mode, byte block, byte *key, byte *serial, byte* data);
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
