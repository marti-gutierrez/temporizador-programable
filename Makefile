# project name
TARGET = temporizador
# microcontroller
MCU = attiny13
F_CPU = 9600000UL
# tools
CC = avr-gcc
OBJCOPY = avr-objcopy
# compilation flags
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o, $(SRC))

default: build/$(TARGET).hex

build/$(TARGET).hex: $(OBJ)
	$(CC) $(CFLAGS) -o build/$(TARGET).elf $?
	$(OBJCOPY) -j .text -j .data -O ihex build/$(TARGET).elf $@
	avr-size --format=avr --mcu=$(MCU) build/$(TARGET).elf


build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinc

clean:
	rm -f build/*.o
	rm -f build/*