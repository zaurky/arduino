#include "rfid.h"


Rfid::Rfid(int ack_pin) {
    _nfc = new MFRC522(SAD, RST);
    _ack_led = new Led(ack_pin);
}


bool Rfid::init() {
    if (_is_init != 0) {
        return false;
    }
    // Initialize the MFRC522 board after 2s to be able to see logs
    // on leonardo.
    delay(2000);
    _is_init = 1;

    Serial.println("Looking for MFRC522.");
    _nfc->begin();

    // Get the firmware version of the RFID chip
    byte version = _nfc->getFirmwareVersion();
    if (! version) {
        Serial.print("Didn't find MFRC522 board.");
        return false;
    }

    Serial.print("Found chip MFRC522 ");
    Serial.print("Firmware ver. 0x");
    Serial.print(version, HEX);
    Serial.println(".");
    return true;
}


bool Rfid::self_test() {
    if (_nfc->digitalSelfTestPass()) {
        Serial.print("Digital self test by MFRC522 passed.");
        return true;
    }
    Serial.print("Digital self test by MFRC522 failed.");
    return false;
}


bool Rfid::read_block(int i, byte* data) {
    byte status;

    // Reading block i from the tag into data.
    status = _nfc->readFromTag(i, data);
    return status == MI_OK;
}


void Rfid::print_block(int i, byte* data) {
    Serial.print("Authenticated block nb. 0x");
    Serial.println(i, HEX);

    // If there was no error when reading; print all the hex
    // values in the data.
    for (int j = 0; j < 15; j++) {
        Serial.print(data[j], HEX);
        Serial.print(", ");
    }
    Serial.println(data[15], HEX);
}


bool Rfid::get_tag(byte* data, byte* serial) {
    byte status;

    // Send a general request out into the aether. If there is a tag in
    // the area it will respond and the status will be MI_OK.
    status = _nfc->requestTag(MF1_REQIDL, data);

    if (status != MI_OK) {
        return false;
    }

    // calculate the anti-collision value for the currently detected
    // tag and write the serial into the data array.
    status = _nfc->antiCollision(data);
    memcpy(serial, data, 5);

    // Select the tag that we want to talk to. If we don't do this the
    // chip does not know which tag it should talk if there should be
    // any other tags in the area..
    _nfc->selectTag(serial);

    return true;
}


void Rfid::release_tag(bool success) {
    // Stop the tag and get ready for reading a new tag.
    _nfc->haltTag();

    if (success) {
        _ack_led->on();
        delay(500);
        _ack_led->off();
        delay(2000);
    }
}


void Rfid::print_tag(byte* data, byte* serial) {
    Serial.println("Tag detected.");
    Serial.print("Type: ");
    Serial.print(data[0], HEX);
    Serial.print(", ");
    Serial.println(data[1], HEX);

    Serial.println("The serial nb of the tag is:");
    for (int i = 0; i < 3; i++) {
        Serial.print(serial[i], HEX);
        Serial.print(", ");
    }
    Serial.println(serial[3], HEX);
}


bool Rfid::auth_and_read(byte mode, byte block, byte *key, byte *serial,
                         byte *data, bool print) {
    bool success = true;

    if (_nfc->authenticate(mode, block, key, serial) == MI_OK) {
        if (!read_block(block, data)) {
            success = false;
#ifdef DEBUG
            if (print) {
                Serial.println("Read failed.");
            }
        } else {
            if (print) {
                print_block(block, data);
            }
#endif
        }
    }
    return success;
}


void Rfid::choose_setup(short setup) {
    if (setup == KEYINIT) {
        _mode = MF1_AUTHENT1A;
        _key = key_init;
    } else if (setup == KEYMINE) {
        _mode = MF1_AUTHENT1B;
        _key = key_mine;
    } else {
        Serial.println("wrong setup value");
        _mode = MF1_AUTHENT1A;
        _key = key_init;
    }
}


long Rfid::get_serial() {
    bool success = true;
    long res = 0;
    byte data[MAX_LEN];
    byte serial[5];

    if (!get_tag(data, serial)) {
        return 0;
    }

    for (int i = 0; i < 3; i++) {
        res |= serial[i];
        res = (res << 8);
    }
    res |= serial[3];

    // read one block else the tag will not be closed correctly ...
    auth_and_read(_mode, 0, _key, serial, data, false);

    release_tag(success);
    return res;
}


void Rfid::read(short nb_block) {
    bool success = true;
    byte data[MAX_LEN];
    byte serial[5];

    if (!get_tag(data, serial)) {
        return;
    }

#ifdef DEBUG
    print_tag(data, serial);
#endif

    // Assuming that there are only 64 blocks of memory in this chip.
    for (int i = 0; i < nb_block; i++) {
        // Try to authenticate each block.
        if (!auth_and_read(_mode, i, _key, serial, data, true)) {
            success = false;
#ifdef DEBUG
            Serial.print("Access denied at block nb. 0x");
            Serial.println(i, HEX);
#endif
            break;
        }
    }
    release_tag(success);
}
