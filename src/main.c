#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "common.h"

#define F_CPU 9600000UL

#define BTN1_RESET PB5
#define BTN2_INC PB4
#define BTN3_START PB3
#define CLK_595 PB2
#define DATA_595 PB1
#define LATCH_595 PB0

const unsigned char gDisplay7[] PROGMEM = {
    191, // Numero 0 en binario es : 10111111
    134, // Numero 1 en binario es : 10000110
    219, // Numero 2 en binario es : 11011011
    207, // Numero 3 en binario es : 11001111
    230, // Numero 4 en binario es : 11100110
    237, // Numero 5 en binario es : 11101101
    253, // Numero 6 en binario es : 11111101
    135, // Numero 7 en binario es : 10000111
    255, // Numero 8 en binario es : 11111111
    239, // Numero 9 en binario es : 11101111
    '\0'};

static unsigned char counter[] = {0, 0, 0, 0, '\0'};
static void init_timer0(void);
// void inc_counter_minutes(void);
// void dec_counter_minutes(void);
void shift595_write(unsigned short data);
void show_display7(unsigned char *digit);

int main()
{
  DDRB |= (1 << CLK_595 | 1 << DATA_595 | 1 << LATCH_595); // Output pins
  DDRB &= ~(1 << BTN2_INC | 1 << BTN3_START);              // input pins
  while (1)
  {
    show_display7(counter);
  }
}

void show_display7(unsigned char *digit)
{
  static unsigned char i = 0;
  if (i > 4)
    i = 0;
  unsigned short word = 0x00ff & pgm_read_byte(&gDisplay7[*(digit + i)]);
  word |= 0xff << 8;
  word &= ~(1 << 8 + i);
  shift595_write(word);
  _delay_ms(1);
  i++;
}

static void init_timer0(void)
{
}

void shift595_write(unsigned short data)
{
  for (char i = 15; i != -1; i--)
  {
    CLEAR_BIT(PORTB, LATCH_595);
    CLEAR_BIT(PORTB, CLK_595);
    _delay_ms(1);
    (data & (1 << i)) ? SET_BIT(PORTB, DATA_595) : CLEAR_BIT(PORTB, DATA_595);
    SET_BIT(PORTB, CLK_595);
    _delay_ms(1);
  }
  SET_BIT(PORTB, LATCH_595);
}
