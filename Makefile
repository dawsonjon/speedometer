MCU=atmega16
CC=avr-gcc
OBJCOPY=avr-objcopy
# optimize for size:
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues

all: speedometer.hex

speedometer.hex : speedometer.out 
	$(OBJCOPY) -R .eeprom -O ihex speedometer.out speedometer.hex 

speedometer.out : speedometer.o sevenseg.o timer.o uart.o buffer.o
	$(CC) $(CFLAGS) -o speedometer.out -Wl,-u,vfprintf -lprintf_flt -lm -Wl,-u,vfscanf -lscanf_flt -lm speedometer.o sevenseg.o timer.o uart.o buffer.o

speedometer.o : speedometer.c
	$(CC) $(CFLAGS) -Os -c speedometer.c

sevenseg.o : sevenseg.c sevenseg.h
	$(CC) $(CFLAGS) -Os -c sevenseg.c

uart.o : uart.c uart.h
	$(CC) $(CFLAGS) -Os -c uart.c

timer.o : timer.c timer.h
	$(CC) $(CFLAGS) -Os -c timer.c

buffer.o : buffer.c buffer.h
	$(CC) $(CFLAGS) -Os -c buffer.c

# erase the AVR before it is programmed
load: speedometer.hex
	sudo uisp -dlpt=/dev/parport0 --erase  -dprog=dapa
	sudo uisp -dlpt=/dev/parport0 --upload if=speedometer.hex -dprog=dapa  -v=3 --hash=32

clean:
	rm -f *.o *.map *.out
