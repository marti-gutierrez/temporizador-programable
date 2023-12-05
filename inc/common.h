#ifndef _COMMON_H_
#define _COMMON_H_

#include <avr/io.h>
#include <avr/sfr_defs.h>

#define SET_BIT(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define CLEAR_BIT(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

#endif // _COMMON_H_