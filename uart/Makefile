CC=msp430-gcc
LD=msp430-gcc
MCU=msp430g2553
CFLAGS= -mmcu=$(MCU) -Wall -Os -c

TARGET=demo-uart.elf

$(TARGET): main.o uart.o
	$(LD) -mmcu=$(MCU) main.o uart.o -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

uart.o: uart.c uart.h
	$(CC) $(CFLAGS) uart.c -o uart.o

install:
	mspdebug rf2500 "prog $(TARGET)"

clean:
	rm -f *.o *.elf


