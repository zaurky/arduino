EXEC=alarm
PORT=/dev/ttyACM0


GPP=avr-g++
GCC=avr-gcc
BINARY=avr-objcopy
DUDE=avrdude

GPPOPT=-c -g -Os -w -Wl,--gc-sections \
	-fno-exceptions -ffunction-sections -fdata-sections \
	-mmcu=atmega32u4 -DF_CPU=16000000L -DARDUINO=22
GCCOPT=-Os -Wl,--gc-sections -mmcu=atmega32u4
BINARYOPT=-O ihex -R .eeprom
DUDEOPT=-patmega32u4 -cavr109 -b57600 -D

CPPLIB=-I arduino -I libraries

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)


all: $(EXEC).hex
ifeq (,$(wildcard $(PORT)))
	echo "\n$(PORT) does not exist! Exiting..."
else
	(./utils/reset.py $(PORT) \
		&& sleep 2 \
		&& $(DUDE) $(DUDEOPT) -P $(PORT) -U "flash:w:$<")
endif

$(EXEC).hex: $(EXEC).elf
	$(BINARY) $(BINARYOPT) $< $@

$(EXEC).elf: $(EXEC).o
	$(GCC) $(GCCOPT) -o $@ $< libraries/*.o core/core.a -L core -lm

$(EXEC).o: library

$(EXEC).cpp: project/$(EXEC).ino
	(echo '#include "Arduino.h"\n\n' > "$(EXEC).cpp" \
		&& cat "project/$(EXEC).ino" >> "$(EXEC).cpp")

library:
	(cd libraries && $(MAKE))

%.o: %.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<

.PHONY: clean

clean:
	(cd libraries && $(MAKE) $@)
	rm -rf *.o *.hex *.elf *.cpp
