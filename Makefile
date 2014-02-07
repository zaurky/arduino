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


all: $(EXEC)

alarm: alarm.hex
	@echo "build $@ done"

transmitter: transmitter.hex
	@echo "build $@ done"

%.hex: %.elf
	$(BINARY) $(BINARYOPT) $< $@
ifeq (,$(wildcard $(PORT)))
	@echo "\n$(PORT) does not exist! Exiting..."
else
	@(./utils/reset.py $(PORT) \
		&& sleep 2 \
		&& $(DUDE) $(DUDEOPT) -P $(PORT) -U "flash:w:$<")
endif

%.elf: library %.o
	$(GCC) $(GCCOPT) -o $@ $*.o libraries/*.o core/core.a -L core -lm

library:
	@(cd libraries && $(MAKE))

%.o: %.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<

%.cpp: project/%.ino
	@(echo '#include "Arduino.h"\n\n' > "$@" && cat "$<" >> "$@")

.PHONY: clean

clean:
	@(cd libraries && $(MAKE) $@)
	@rm -rf *.o *.hex *.elf *.cpp
