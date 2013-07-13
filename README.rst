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
=== =========== =================================
