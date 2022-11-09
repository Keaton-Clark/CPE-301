#include <avr/io.h>
#include <stdio.h>
#include "io.h"

#define TIMER_RESET(C) TCCR1B &= 0xF8;TIFR1 |= 0x01;TCNT1 = (uint16_t) (0xFFFF - freq_table[C]);TCCR1B |= 0x01
#define TIMER_WAIT while (!(TIFR1 & 0x01))
#define TICKS(F) (uint16_t)(F_CPU/(2*F)) 

uint16_t freq_table[256] = {
	['A'] = TICKS(440),	
	['B'] = TICKS(494),	
	['C'] = TICKS(523),
	['D'] = TICKS(587),	
	['E'] = TICKS(659),	
	['F'] = TICKS(698),	
	['G'] = TICKS(784),	
};

int main () {
	uart_init(9600);
	pin_t out = new_pin(12);
	char c = 'A';
	for(;;) {
		if (uart_available())
			c = uart_read();
		TIMER_RESET(c);
	  	TIMER_WAIT;
	  	toggle_pin(out);
	}
}
