==========================================================
Simple GPS Speedometer
==========================================================

Jonathan P Dawson

2013

Requirements
============

You need the following packages to build the speedometer:

  + avr-gcc
  + avr-libc
  + uisp

Build
=====

Compile the source code:

> make

Program
=======

Set the AVR fuses:

> ./set_fuses

Program the AVR:

> make load

Components
==========

=== =========== =================================
ref designation description
=== =========== =================================
1   IC1         ATMEGA16_16PU AVR Microcontroller
2   T1          P55NF06L 10A MOSFET
3   T2          P55NF06L 10A MOSFET
4   C1          22pf ceramic capacitor
5   C2          22pf ceramic capacitor
6   C3          1nf ceramic capacitor
7   C4          1nf ceramic capacitor
8   X1          16 MHz xtal
9   R1          10K resistor
10  GPS 1       GPS Module
=== =========== =================================

Circuit
=======

.. image:: https://raw.github.com/dawsonjon/speedometer/master/circuit.png

An Atmel AVR ATMEGA16 forms the basis of this project. The 16PU part is
available as a 40 pin DIP allowing easy prototyping using strip-board. The
Microcontroller setup is about as minimal as you can get, using a 16 MHz
crystal as a clock, and a pull-up resistor for the reset.

Programming is achieved using a 40 pin DIP test clip, connected to a PC
parallel port.

I am using a two digit display, but a third digit could be added quite easily.
Since the ready made displays I had available were rather too small, I formed
the display from low current 3mm LEDs, using 3 LEDs in series to form each
segment. Since the LEDs are connected in series, there is no need for a current
limiting resistor. The IO pins on the ATMEGA16 seem to be capable of powering a
single segment, but the common cathode (driving up to 7 segments) uses a power
MOSFET to avoid damage to the pins. The 10A MOSFET is overkill, but they
may be driven directly from an IO pin, and I had several available in my junk
box.

A GPS module is used to form the speed sensor. At first I had considered using
a hall sensor attached to the prop-shaft, but GPS modules turn out to be cheap
and easy.

.. image:: https://raw.github.com/dawsonjon/speedometer/master/hardware.jpg

Firmware
========

Again the firmware is pretty simple.

The timer and UART drivers are taken from `AVR lib
<http://www.procyonengineering.com/embedded/avr/avrlib/>`_. The source code
needed to be modified to use a newer naming convention for interrupt events. The
UART code also needed some modification to make reads from the UART blocking.

The application is divided into:
 
+ seven_segment.c - Seven segment display driver 
+ speed.c - Extract a speed in km/h from NMEA messages from the GPS module.  
+ speedometer.c - The main application.

The main application reads the speed from the GPS module, and converts to mph.
A safety factor of 6% is added to the indicated speed. This is because the GPS
module gives the speed in a horizontal direction, which would cause the
speedometer to under read. A 6% safety factor more than compensates for the
effect of a 1 in 3 gradient. I consider a 1 in 3 gradient to be the steepest
slope that a car is likely to encounter.

When the device powers up, a flashing pattern is displayed to indicate that a
speed has not yet been received. This could take as long as 30 seconds.

LCD Version
===========


The initial tests of the speedometer proved to be a little disappointing. The
speedometer seemed to work well, but the readout was almost impossible to read
in bright sunshine. 

A 16x4 character LCD display was chosen. A back-lit display was chosen so that
it could be read in the dark and in bright sunshine. I chose a green LCD
because I liked the colour, red and blue ones are also available!  A 4 row LCD
allows the large numerals to be formed by grouping together user defined
characters. The display only has space for 8 user defined characters, so it
takes a bit of imagination to find a set that will form all the digits from
0-9. The new LCD display was wired into the existing circuit.

.. image:: https://raw.github.com/dawsonjon/speedometer/master/circuit_lcd.png

The two digits for the speed use up the first 6 columns of the display. The
display could have been extended to three digits to allow for higher speeds, or
a kph representation. For my purposes, two digits is quite adequate, and this
leaves another 10 x 4characters to play with.

Of all the information that can be extracted from the GPS, I decided that the
date and time were the most useful. The date and time require a little
manipulation, since the GPS provides the time in UTC. To allow for daylight
saving (British Summer Time), I added a function to work out from the time of
year whether GMT or BST should be used. This required a function that
calculates the day of the week, since the clocks change on the last Sunday of
March and October. After working out whether to add an hour, a check is
performed to see whether the date does not need to change (which could
happen in the hour before midnight).


.. image:: https://raw.github.com/dawsonjon/speedometer/master/lcd_readout.png
