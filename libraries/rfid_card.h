#ifndef rfid_card_h
#define rfid_card_h


#define sensor_rfid0 0xa306408b // [A3, 6, 40, 8B]
#define sensor_rfid1 0x93367f81 // [93, 36, 7F, 81]
#define sensor_rfid2 0x8e49dc84 // [8E, 49, DC, 84]


class Card {
    public:
        Card(long code);
        bool exists();
        long get_message();
    private:
        long _code;
};


#endif
