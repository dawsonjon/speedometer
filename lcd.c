#include "lcd.h"
#define F_CPU 16000000UL
#include <util/delay.h>

//define the symols used for bignum characters
char symbol [10][4][3] = {
	
//0
{{4,  3,  5},
 {1, ' ', 0},
 {1, ' ', 0},
 {6,  2,  7}},
//1
{{' ', ' ', 5},
 {' ', ' ', 0},
 {' ', ' ', 0},
 {' ', ' ', 7}},
//2
{{4,  3,  5},
 {4, 3, 0},
 {1, ' ', ' '},
 {6,  2,  7}},
//3
{{4,  3,  5},
 {' ', 3, 0},
 {' ', ' ', 0},
 {6,  2,  7}},
//4
{{4, ' ',  5},
 {1, 3, 0},
 {' ', ' ', 0},
 {' ',  ' ',  7}},
//5
{{4,  3,  5},
 {1,  3,  5},
 {' ', ' ', 0},
 {6,  2,  7}},
//6
{{4,  3,  5},
 {1,  3,  5},
 {1, ' ', 0},
 {6,  2,  7}},
//7
{{4,  3,  5},
 {' ', ' ', 0},
 {' ', ' ', 0},
 {' ', ' ', 7}},
//8
{{4,  3,  5},
 {1,  3, 0},
 {1, ' ', 0},
 {6,  2,  7}},
//9
{{4,  3,  5},
 {1, 3, 0},
 {' ', ' ',  0},
 {6,  2,  7}}};

// output byte value to the lcd
void lcd_io( uint8_t value )
{
   _delay_us(10);
   DATA_PORT = value;
   _delay_us(10);
   STB_PORT |= (1 << STB_PIN);
   _delay_us(10);
   STB_PORT &= ~(1 << STB_PIN);
   _delay_us(10);
}

// output the instruction byte in value to the lcd
void lcd_instruction( uint8_t value )
{
   RS_PORT &= ~(1 << RS_PIN);
   lcd_io(value);         
   _delay_us(50);
}

// output the data byte in value to the lcd
void lcd_write( uint8_t value )
{
   RS_PORT |= (1 << RS_PIN);
   lcd_io(value);
}

// lcd initialisation
void lcdInit()
{
   DATA_DIRECTION = 0xff;
   RS_DIRECTION |= (1 << RS_PIN);
   STB_DIRECTION |= (1 << STB_PIN);
   RS_PORT &= ~(1 << RS_PIN);
   STB_PORT &= ~(1 << STB_PIN);

   _delay_ms(100);
   lcd_instruction( 0x38 );  // set 8 bits
   _delay_us(50);
   lcd_instruction( 0x38 );  // set 8 bits
   _delay_us(50);
   lcd_instruction( 0x0C );  // display_on | auto_increment | ~cursor | ~blink
   _delay_us(50);
   lcd_instruction( 0x01 );  // clear display
   _delay_ms(2);
   lcd_instruction( 0x06 );  // auto incrment no shift

   //setup symbols for bignum charaters
   lcd_define(0, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C);
   lcd_define(1, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07);
   lcd_define(2, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00);
   lcd_define(3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F);
   lcd_define(4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07);
   lcd_define(5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x1C);
   lcd_define(6, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);
   lcd_define(7, 0x1C, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);

}

void lcd_clear()
{
   lcd_instruction( 0x01 );  // clear display
   _delay_ms(2);
}

void lcd_position( uint8_t x )
{
   lcd_instruction( 0x80 + x );
}

void lcd_line1()
{
   lcd_instruction( 0x80 );
}

void lcd_line2()
{
   lcd_instruction( 0xA8 );
}

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
) 
{
   lcd_instruction( 0x40 | ( x << 3 ) );
   lcd_write( b0 );
   lcd_write( b1 );
   lcd_write( b2 );
   lcd_write( b3 );
   lcd_write( b4 );
   lcd_write( b5 );
   lcd_write( b6 );
   lcd_write( b7 );
}

void big_num(int column, int number)
{
	lcd_position(column);
	lcd_write(symbol[number][0][0]);
	lcd_write(symbol[number][0][1]);
	lcd_write(symbol[number][0][2]);
	lcd_position(column + 0x40);
	lcd_write(symbol[number][1][0]);
	lcd_write(symbol[number][1][1]);
	lcd_write(symbol[number][1][2]);
	lcd_position(column + 0x10);
	lcd_write(symbol[number][2][0]);
	lcd_write(symbol[number][2][1]);
	lcd_write(symbol[number][2][2]);
	lcd_position(column + 0x50);
	lcd_write(symbol[number][3][0]);
	lcd_write(symbol[number][3][1]);
	lcd_write(symbol[number][3][2]);
}

void lcd_print(char * string)
{
  int i;
  char character;
  while(1)
  {
    character = string[i++];
    if(!character) return;
    lcd_write(character);
  }
}
