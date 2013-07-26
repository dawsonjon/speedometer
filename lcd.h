#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <stdint.h>
#include "lcd_conf.h"

// output byte value to the lcd
void lcd_io( uint8_t value );

// output the instruction byte in value to the lcd
void lcd_instruction( uint8_t value );

// output the data byte in value to the lcd
void lcd_write( uint8_t value );

// lcd initialisation
void lcdInit();

void lcd_clear();

void lcd_position( uint8_t x );

void lcd_line1();

void lcd_line2();

void lcd_define( 
   uint8_t x,
   uint8_t b0, 
   uint8_t b1, 
   uint8_t b2, 
   uint8_t b3, 
   uint8_t b4, 
   uint8_t b5, 
   uint8_t b6,
   uint8_t b7
);

void big_num(int column, int number);
void lcd_print(char * string);

#endif
