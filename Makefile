EXEC=alarm.bin
PORT=/dev/ttyACM0
MAXMEM=28672


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

# DEPS lists per target
READER_SRC=libraries/CardReader.cpp
READER_OBJ=$(READER_SRC:.cpp=.o)

ALARM_SRC=libraries/alarm.cpp libraries/blink2.cpp libraries/buzzer.cpp \
		  libraries/RCSwitch.cpp libraries/sensor.cpp \
		  libraries/serialconsole.cpp libraries/utils.cpp
ALARM_OBJ=$(ALARM_SRC:.cpp=.o)

TRAMITTER_SRC=libraries/transmitter.cpp libraries/RCSwitch.cpp
TRAMITTER_OBJ=$(TRAMITTER_SRC:.cpp=.o)


all: $(EXEC)

%.bin: %.hex
	@echo "build $@ done"

%.hex: %.elf
	$(BINARY) $(BINARYOPT) $< $@
ifeq (,$(wildcard $(PORT)))
	@echo "\n$(PORT) does not exist! Exiting..."
else
	@([ $(stat -c %s $<) -lt $(MAXMEM) ] \
		&& ./utils/reset.py $(PORT) \
		&& sleep 2 \
		&& $(DUDE) $(DUDEOPT) -P $(PORT) -U "flash:w:$@")
endif

# add the .ino file and its dependencies
reader.elf: reader.o $(READER_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(READER_OBJ) core/core.a -L core -lm

alarm.elf: alarm.o $(ALARM_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(ALARM_OBJ) core/core.a -L core -lm

transmitter.elf: transmitter.o $(TRAMITTER_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(TRAMITTER_OBJ) core/core.a -L core -lm

%.o: %.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<

%.cpp: project/%.ino
	@(echo '#include "Arduino.h"\n\n' > "$@" && cat "$<" >> "$@")

libraries/%.o: libraries/%.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<


.PRECIOUS: %.hex
.PHONY: clean

clean:
	@(cd libraries && $(MAKE) $@)
	@rm -rf *.o *.hex *.elf *.cpp libraries/*.o
