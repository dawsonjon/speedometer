#include "sevenseg.h"

void sevensegInit(void){
  DIGIT_A_DIRECTION |= (1 << DIGIT_A_PIN);
  DIGIT_B_DIRECTION |= (1 << DIGIT_B_PIN);
  SEGMENT_A_DIRECTION |= (1 << SEGMENT_A_PIN);
  SEGMENT_B_DIRECTION |= (1 << SEGMENT_B_PIN);
  SEGMENT_C_DIRECTION |= (1 << SEGMENT_C_PIN);
  SEGMENT_D_DIRECTION |= (1 << SEGMENT_D_PIN);
  SEGMENT_E_DIRECTION |= (1 << SEGMENT_E_PIN);
  SEGMENT_F_DIRECTION |= (1 << SEGMENT_F_PIN);
  SEGMENT_G_DIRECTION |= (1 << SEGMENT_G_PIN);
  DIGIT_A_PORT |= (1 << DIGIT_A_PIN);
  DIGIT_B_PORT |= (1 << DIGIT_B_PIN);
  SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
  SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
  SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
  SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
  SEGMENT_E_PORT |= (1 << SEGMENT_E_PIN);
  SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
  SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
}

void display_off(){
  DIGIT_A_PORT &= ~(1 << DIGIT_A_PIN);
  DIGIT_B_PORT &= ~(1 << DIGIT_B_PIN);
}

void sevensegSetDigit(uint8_t i)
{
  switch(i)
  {
    case 0:
      DIGIT_A_PORT |= (1 << DIGIT_A_PIN);
      DIGIT_B_PORT &= ~(1 << DIGIT_B_PIN);
      break;
    case 1:
      DIGIT_A_PORT &= ~(1 << DIGIT_A_PIN);
      DIGIT_B_PORT |= (1 << DIGIT_B_PIN);
      break;
    case 2:
      DIGIT_A_PORT &= ~(1 << DIGIT_A_PIN);
      DIGIT_B_PORT &= ~(1 << DIGIT_B_PIN);
      break;
    case 3:
      DIGIT_A_PORT &= ~(1 << DIGIT_A_PIN);
      DIGIT_B_PORT &= ~(1 << DIGIT_B_PIN);
      break;
    default:
      DIGIT_A_PORT &= ~(1 << DIGIT_A_PIN);
      DIGIT_B_PORT &= ~(1 << DIGIT_B_PIN);
      break;
  }
}

void sevensegSetSegments(uint8_t i)
{
  switch(i)
  {
    case 0:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT |= (1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT &= ~(1 << SEGMENT_G_PIN);
      break;
    case 1:
      SEGMENT_A_PORT &= ~(1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT &= ~(1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT &= ~(1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT &= ~(1 << SEGMENT_G_PIN);
      break;
    case 2:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT &= ~(1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT |= (1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT &= ~(1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    case 3:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT &= ~(1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    case 4:
      SEGMENT_A_PORT &= ~(1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT &= ~(1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    case 5:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT &= ~(1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    case 6:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT &= ~(1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT |= (1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    case 7:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT &= ~(1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT &= ~(1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT &= ~(1 << SEGMENT_G_PIN);
      break;
    case 8:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT |= (1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    case 9:
      SEGMENT_A_PORT |= (1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT |= (1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT |= (1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT |= (1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT |= (1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT |= (1 << SEGMENT_G_PIN);
      break;
    default:
      SEGMENT_A_PORT &= ~(1 << SEGMENT_A_PIN);
      SEGMENT_B_PORT &= ~(1 << SEGMENT_B_PIN);
      SEGMENT_C_PORT &= ~(1 << SEGMENT_C_PIN);
      SEGMENT_D_PORT &= ~(1 << SEGMENT_D_PIN);
      SEGMENT_E_PORT &= ~(1 << SEGMENT_E_PIN);
      SEGMENT_F_PORT &= ~(1 << SEGMENT_F_PIN);
      SEGMENT_G_PORT &= ~(1 << SEGMENT_G_PIN);
  }
}

/*update display 250 times a second*/
uint8_t update_display(uint8_t digit,
                       uint8_t digit_0,
                       uint8_t digit_1)
{
    if(digit == 1)
    {
      digit = 0;
    }
    else
    {
      digit++;
    }

    sevensegSetDigit(digit);
    switch(digit)
    {
      case 0:
        sevensegSetSegments(digit_0);
        break;
      case 1:
        sevensegSetSegments(digit_1);
        break;
      default:
        break;
    }
    return digit;
}

