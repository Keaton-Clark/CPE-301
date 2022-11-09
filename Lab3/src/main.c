#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "io.h"

int main (void) {
	pin_t btn[2] = {new_pin(4), new_pin(3)};
	pin_t led[4] = {new_pin(10), new_pin(11), new_pin(12), new_pin(13)};
	uart_init(9600);
	for(;;) {
		uart_put_char(uart_read_char(), stdout);
		for (int i = 0; i < 4; ++i) {
			write_pin(led[i], ((((!!read_pin(btn[0]))<<1) | (!!read_pin(btn[1]))) == i));
		}
	}
}
