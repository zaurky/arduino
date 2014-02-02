#!/bin/bash

PORT="/dev/ttyACM0"
PROJECT="Transmitter"
LIBS="blink2 RCSwitch buzzer sensor alarm utils serialconsole transmitter"

# convert ino sketch file into a .cpp
echo -e '#include "Arduino.h"\n\n' > "$PROJECT.cpp"
cat "$PROJECT/$PROJECT.ino" >> "$PROJECT.cpp"


LIB_INCLUDE="-I ../../arduino/ -I ../`echo $LIBS | sed -e 's/ / -I ..\//'g`"

OPTIONS="-c -g -Os -w -Wl,--gc-sections
    -fno-exceptions -ffunction-sections -fdata-sections
    -mmcu=atmega32u4 -DF_CPU=16000000L -DARDUINO=22"

for lib in $LIBS; do
    cd libraries/${lib}
    avr-g++ $OPTIONS $LIB_INCLUDE -o ${lib}.o ${lib}.cpp
    cd ../..
done

LIB_INCLUDE="-I arduino/ -I libraries/`echo $LIBS | sed -e 's/ / -I libraries\//'g`"
avr-g++ $OPTIONS $LIB_INCLUDE -o "$PROJECT.o" "$PROJECT.cpp"

avr-gcc -Os -Wl,--gc-sections -mmcu=atmega32u4 -o "$PROJECT.elf" "$PROJECT.o" libraries/*/*.o  core/core.a -L core -lm

avr-objcopy -O ihex -R .eeprom "$PROJECT.elf" "$PROJECT.hex"

./utils/reset.py "$PORT"

sleep 2

avrdude -patmega32u4 -cavr109 -P "$PORT" -b57600 -D -U "flash:w:$PROJECT.hex"
