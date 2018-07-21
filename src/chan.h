#ifndef _CHAN_H_
#define _CHAN_H_

#include <avr/io.h>

void chan_init();

void chan_val(uint8_t chan, uint8_t val);
void chan_z(uint8_t chan, uint8_t z);
#endif
