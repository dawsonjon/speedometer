#include <avr/io.h>
#include <avr/wdt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "lcd.h"
#include "gps.h"

static FILE mystdin = FDEV_SETUP_STREAM(uartSendByte, uartGetByte, _FDEV_SETUP_RW);

int main()
{

  stdin  = & mystdin;
  stdout = & mystdin;
  stderr = & mystdin;

  double speed;
  char buffer [9];
  int digit_0;
  int digit_1;
  int i;

  /*Initialise*/
  timerInit();
  uartInit();
  lcdInit();
  uartSetBaudRate(9600);
  wdt_enable(WDTO_2S);

  /*Print Debug Text*/
  printf("GPS Speedometer - Jonathan P Dawson 2013-06-26\r\n");

  /*Main application loop*/
  while(1)
  {
	  /* Obtain speed in knots */

	  speed = get_speed_knots();

          /* Convert to mph */

	  speed *= 1.15077945;

	  /* 6% safety factor */

          /*Think that gps velocity is much more acurate than this. However
	    the GPS reports the horizontal velocity. If you are going up or
	    down a steep hill, then the speedometer will under read.

            I have taken 1:3 gradient as being the steepest hill that
	    is likely to be encountered. On this slope, the vehicle will be 
	    travelling 5.4% faster than the speedometer is reading. To allow 
	    for this, I have added a safety factor of 6% so that the speedometer
	    does not under read. 

            This is still within the acceptable accuracy for a speedometer
	    which according top ECE regulation 39 section 5.3 must be::
	   
		    actual <= indicated <= actual * 1.1 +  4km/h */


	  speed *= 1.06;

	  /* Output to console for debug purposes */

	  printf("speed: %f  mph\r\n", speed);

	  /* Convert to two digit representation */
	  if (speed > 99.0)
	  {
		  digit_0 = 9;
		  digit_1 = 9;
	  }
	  else if (speed < 0.0)
	  {
		  digit_0 = 0;
		  digit_1 = 0;
	  }
	  else
          {
		  //speed += 0.5; //rounding
		  for(digit_0=0; speed >= 10.0; speed-=10.0) digit_0++;
		  for(digit_1=0; speed >= 1.0; speed-=1.0) digit_1++;
	  }

	  /*Display speed in large numbers*/
	  big_num(0, digit_0);
	  big_num(3, digit_1);
	  lcd_position(0x56);

	  /*Display speed units*/
	  lcd_write('m');
	  lcd_write('/');
	  lcd_write('h');

	  /*Display date*/
	  lcd_position(0x08);
	  sprintf(buffer, "%02u-%02u-%02u", get_day(), get_month(), get_year());
	  lcd_print(buffer);

	  /*Display time*/
	  lcd_position(0x48);
	  sprintf(buffer, "%02u:%02u:%02u", get_hour(), get_minute(), get_second());
	  lcd_print(buffer);

          /*display daylight saving time*/
	  lcd_position(0x1D);
          if(is_bst())
          {
	    lcd_print("BST");
          }
	  else
	  {
	    lcd_print("GMT");
	  }

          /*check gps quality*/
	  lcd_position(0x5F);
	  lcd_write(get_gps_good());
      wdt_reset();
  }
  return 0;
}
