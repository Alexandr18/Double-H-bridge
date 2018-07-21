#include "main.h"

int main(void){
	init();	
	for(;;)
		loop();
	return 0;
}


void init(){
	chan_init();
	PORTD |= _BV(PD0) | _BV(PD1) | _BV(PD2) |  _BV(PD3) | _BV(PD4) | _BV(PD5) | _BV(PD6);
	PORTA |= _BV(PA1) | _BV(PA0);
}

void loop(){
	bool ch0z = !(PIND & _BV(PD0));
	bool ch0v = !(PIND & _BV(PD1));
	bool ch1z = !(PINA & _BV(PA1));
	bool ch1v = !(PINA & _BV(PA0));
	bool ch2z = !(PIND & _BV(PD2));
	bool ch2v = !(PIND & _BV(PD3));
	bool ch3z = !(PIND & _BV(PD4));
	bool ch3v = !(PIND & _BV(PD5));
	bool enable = !(PIND & _BV(PD6));
	
	if(enable){
		chan_z(0, ch0z);
		chan_val(0, ch0v);
		chan_z(1, ch1z);
		chan_val(1, ch1v);
		chan_z(2, ch2z);
		chan_val(2, ch2v);
		chan_z(3, ch3z);
		chan_val(3, ch3v);
	}else{
		chan_z(0, 0);
		chan_z(1, 0);
		chan_z(2, 0);
		chan_z(3, 0);
	}
}

