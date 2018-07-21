#include "chan.h"

volatile uint8_t zstate = 0;
volatile uint8_t valstate = 0;

void update_channels();
void update_channel(uint8_t);

void chan_init(){
	PORTB = 0;
	DDRB = 0xFF;
	update_channels();
}

void update_channels(){
	for(int i=0; i<4; i++){
		update_channel(i);
	}
}
void update_channel(uint8_t chan){
	if(chan > 3){
		return;
	}
	uint8_t channel_mask = _BV(chan*2) | _BV(chan*2+1);
	if(bit_is_set(zstate, chan)){
		uint8_t intermediate = PORTB & (~(channel_mask));
		if(bit_is_set(valstate, chan)){
			intermediate |= _BV(chan*2 +1);
		}else{
			intermediate |= _BV(chan*2);
		}
		PORTB = intermediate;
	}else{
		PORTB &= ~(channel_mask);
	}
}

void chan_val(uint8_t chan, uint8_t val){
	if(chan > 3){
		return;
	}
	if(val){
		valstate |= (_BV(chan));
	}else{
		valstate &= ~(_BV(chan));
	}
	update_channel(chan);
}

void chan_z(uint8_t chan, uint8_t z){
	if(chan > 3){
		return;
	}
	if(z){
		zstate |= (_BV(chan));
	}else{
		zstate &= ~(_BV(chan));
	}
	update_channel(chan);
}
