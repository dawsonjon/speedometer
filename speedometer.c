#include <avr/io.h>
#include <stdio.h>

#include "timer.h"
#include "uart.h"
#include "sevenseg.h"

volatile uint8_t count = 0;

/*display values*/
uint8_t digit = 0;
uint8_t digit_0 = 0;
uint8_t digit_1 = 0;

/*executed 250 times per second*/
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
  /*Initialise*/
  sevensegInit();
  timerInit();
  uartInit();

  /*set division to 1 */
  timer1SetPrescaler(TIMER_CLK_DIV1024);

  /*attach timer 1 compare match interrupt to tick function*/
  timerAttach(TIMER1OVERFLOW_INT, tick);

  uartSetBaudRate(9600);

  digit_0 = 9;
  digit_1 = 9;
  while(1);
  return 0;
}
