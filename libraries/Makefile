GPP=avr-g++
GCC=avr-gcc

GPPOPT=-c -g -Os -w -Wl,--gc-sections \
	   -fno-exceptions -ffunction-sections -fdata-sections \
	   -mmcu=atmega32u4 -DF_CPU=16000000L -DARDUINO=22
CPPLIB=-I ../arduino/ -I .

SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(OBJ)

%.o: %.cpp
	$(GPP) $(GPPOPT) $(CPPLIB) -o $@ $<

.PHONY: clean

clean:
	@rm -rf *.o
