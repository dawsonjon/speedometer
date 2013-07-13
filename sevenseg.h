#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <avr/io.h>
#include <stdint.h>
#include "sevenseg_conf.h"

void sevensegInit(void);
void sevensegSetSegments(uint8_t i);
void sevensegSetDigit(uint8_t i);

/*call this ~200 times a second*/
uint8_t update_display(uint8_t digit,
                    uint8_t digit_0,
                    uint8_t digit_1);

#endif
