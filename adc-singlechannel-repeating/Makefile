CC=msp430-gcc
LD=msp430-gcc
MCU=msp430g2553
CFLAGS= -mmcu=$(MCU) -Wall -Os -c

TARGET=demo-adc.elf
OBJECTS= main.o uart.o adc.o

$(TARGET): $(OBJECTS)
	$(LD) -mmcu=$(MCU) $(OBJECTS)  -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

uart.o: uart.c uart.h
	$(CC) $(CFLAGS) uart.c -o uart.o

adc.o: adc.c adc.h
	$(CC) $(CFLAGS) adc.c -o adc.o

install:
	mspdebug rf2500 "prog $(TARGET)"

clean:
	rm -f *.o *.elf


