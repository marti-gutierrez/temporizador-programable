#include "shift595.h"
#include <avr/io.h>
#include "common.h"

#define CLK_595 PB2
#define DATA_595 PB1
#define LATCH_595 PB0

void shift595_init(void)
{
  DDRB |= _BV(CLK_595) | _BV(DATA_595) | _BV(LATCH_595); // output -> clk, data y latch
}

void shift595_write(unsigned char data)
{
  unsigned char buffer = 0x00;
  for (unsigned char i = 8; i > 0; i--)
  {
    CLEAR_BIT(PORTB, LATCH_595);
    __asm __volatile("nop");
    CLEAR_BIT(PORTB, CLK_595);
    (data & (1 << i) == 0) ? CLEAR_BIT(PORTB, DATA_595) : SET_BIT(PORTB, DATA_595);
    SET_BIT(PORTB, CLK_595);
    __asm __volatile("nop");
  }
  SET_BIT(PORTB, LATCH_595);
}