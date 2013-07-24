#include <avr/io.h>
#include <stdio.h>

#include "timer.h"
#include "uart.h"
#include "sevenseg.h"
#include "speed.h"

static FILE mystdin = FDEV_SETUP_STREAM(uartSendByte, uartGetByte, _FDEV_SETUP_RW);

volatile uint16_t count = 0;

/*display values*/
uint8_t waiting = 1;
uint8_t digit = 0;
uint8_t digit_0 = 0;
uint8_t digit_1 = 0;

/*executed 244 times per second*/
void update()
{

  /*update display*/
  digit = update_display
  (
    digit,
    digit_0,
    digit_1
  );
}

/*executed 244 times per second*/
void flash()
{
  if (count == 640) count = 0; else count ++;
  digit = update_display(digit, count>>6, count>>6);
}

int main()
{

  stdin  = & mystdin;
  stdout = & mystdin;
  stderr = & mystdin;

  double speed;

  /*Initialise*/
  sevensegInit();
  timerInit();
  uartInit();

  /*Start LED flash task*/
  timer1SetPrescaler(TIMER_CLK_DIV1);
  timerAttach(TIMER1OVERFLOW_INT, flash);

  uartSetBaudRate(9600);

  printf("GPS Speedometer - Jonathan P Dawson 2013-06-23\r\n");

  while(1)
  {
	  /* Obtain speed in kph */

	  speed = get_speed_kph();

          /* When first message is displayed,
	     stop flashing and start updating the display*/
	  timer1SetPrescaler(TIMER_CLK_DIV1);
	  timerDetach(TIMER1OVERFLOW_INT);
	  timerAttach(TIMER1OVERFLOW_INT, update);

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
		  speed += 0.5; //rounding
		  for(digit_0=0; speed >= 10.0; speed-=10.0) digit_0++;
		  for(digit_1=0; speed >= 1.0; speed-=1.0) digit_1++;
	  }
  }
  return 0;
}
