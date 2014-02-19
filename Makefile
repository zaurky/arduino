PROJECTS=alarm rfid_proxy rfid_reader rfid_firmware_check empty
PORT=/dev/ttyACM0
# for leonardo
BOARD=atmega32u4
MAXMEM=28672
# for UNO
#BOARD=atmega328p
#MAXMEM=32256


GPP=avr-g++
GCC=avr-gcc
BINARY=avr-objcopy
DUDE=avrdude

GPPOPT=-c -g -Os -w -Wl,--gc-sections \
	-fno-exceptions -ffunction-sections -fdata-sections \
	-mmcu=$(BOARD) -DF_CPU=16000000L -DARDUINO=22
GCCOPT=-Os -Wl,--gc-sections -mmcu=$(BOARD)
BINARYOPT=-O ihex -R .eeprom
DUDEOPT=-p$(BOARD) -cavr109 -b57600 -D

CPPLIB=-I arduino -I libraries

# DEPS lists per target
READER_SRC=libraries/CardReader.cpp
READER_OBJ=$(READER_SRC:.cpp=.o)

ALARM_SRC=libraries/alarm.cpp libraries/blink2.cpp libraries/buzzer.cpp \
		  libraries/RCSwitch.cpp libraries/sensor.cpp \
		  libraries/serialconsole.cpp libraries/utils.cpp
ALARM_OBJ=$(ALARM_SRC:.cpp=.o)

TRANSMITTER_SRC=libraries/transmitter.cpp libraries/RCSwitch.cpp \
				libraries/SPI.cpp libraries/MFRC522.cpp libraries/blink2.cpp \
				libraries/rfid.cpp libraries/rfid_card.cpp
TRANSMITTER_OBJ=$(TRANSMITTER_SRC:.cpp=.o)

MODRFID_SRC=libraries/transmitter.cpp libraries/RCSwitch.cpp \
			libraries/SPI.cpp libraries/MFRC522.cpp libraries/blink2.cpp \
			libraries/rfid.cpp
MODRFID_OBJ=$(MODRFID_SRC:.cpp=.o)


PROJECTS_HEX=$(PROJECTS:=.hex)


all: $(PROJECTS_HEX) clean_wip

%.bin: %.hex
ifeq (,$(wildcard $(PORT)))
	@echo "\n$(PORT) does not exist! Exiting..."
else
	@if [ `avr-size $< | tail -n 1 | awk '{print $$2}'` -lt $(MAXMEM) ]; then \
		echo "uploading $@ to $(PORT)"; \
		mv $< $@; \
		(./utils/reset.py $(PORT) \
			&& sleep 2 \
			&& $(DUDE) $(DUDEOPT) -P $(PORT) -U "flash:w:$@"); \
	else \
		echo "$< is too big"; \
	fi
endif

%.hex: %.elf
	$(BINARY) $(BINARYOPT) $< $@
	@echo "build $@ done"

# add the .ino file and its dependencies
alarm.elf: alarm.o $(ALARM_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(ALARM_OBJ) core/core.a -L core -lm

rfid_proxy.elf: rfid_proxy.o $(TRANSMITTER_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(TRANSMITTER_OBJ) core/core.a -L core -lm

rfid_reader.elf: rfid_reader.o $(MODRFID_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(MODRFID_OBJ) core/core.a -L core -lm

rfid_firmware_check.elf: rfid_firmware_check.o $(MODRFID_OBJ)
	$(GCC) $(GCCOPT) -o $@ $< $(MODRFID_OBJ) core/core.a -L core -lm

empty.elf: empty.o
	$(GCC) $(GCCOPT) -o $@ $< core/core.a -L core -lm

%.o: %.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<

%.cpp: project/%.ino
	@(echo '#include "Arduino.h"\n\n' > "$@" && cat "$<" >> "$@")

libraries/%.o: libraries/%.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<

console:
	@(./utils/read_serial.py -D $(PORT))

.PRECIOUS: %.hex
.PHONY: clean

clean_wip:
	@rm -rf *.o *.elf *.cpp libraries/*.o

clean: clean_wip
	@rm -rf *.hex
