#include "common.h"
#include <util/delay.h>
#define F_CPU 9600000UL

#define BTN1_RESET PB5
#define BTN2_INC PB4
#define BTN3_START PB3

int main()
{
  SET_BIT(DDRB, PB0);
  CLEAR_BIT(PORTB, PB0);
  while (1)
  {
    PORTB ^= 1 << PB0;
    _delay_ms(500);
  }
}