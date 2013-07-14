#include <avr/io.h>
#include <stdio.h>

#include "timer.h"
#include "uart.h"
#include "sevenseg.h"

static FILE mystdin = FDEV_SETUP_STREAM(uartSendByte, uartGetByte, _FDEV_SETUP_RW);

volatile uint8_t count = 0;

/*display values*/
uint8_t digit = 0;
uint8_t digit_0 = 0;
uint8_t digit_1 = 0;

/*executed 244 times per second*/
void tick()
{
  /*update display*/
  digit = update_display
  (
    digit,
    digit_0,
    digit_1
  );
}

int main()
{

  stdin  = & mystdin;
  stdout = & mystdin;
  stderr = & mystdin;

  int speed;

  /*Initialise*/
  sevensegInit();
  timerInit();
  uartInit();

  /*set division to 1 */
  timer1SetPrescaler(TIMER_CLK_DIV1);

  /*attach timer 1 compare match interrupt to tick function*/
  timerAttach(TIMER1OVERFLOW_INT, tick);

  uartSetBaudRate(9600);

  while(1)
  {

	  scanf("%u", &speed);
	  printf("speed: %2u mph\r\n", speed);

	  for(digit_0=0; speed > 10; speed-=10) digit_0++;
	  digit_1 = speed;
  }
  return 0;
}
