#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "io.h"

int main (void) {
	pin_t output = new_pin(4);
	pin_t input = new_pin(2);
	uart_init(9600);
	uint8_t prev_state = read_pin(input);
	for(int i;;) {
		if (read_pin(input) && !prev_state) {
			write_pin(output, HIGH);
			printf("Switch Closed\n");
			prev_state = HIGH;
		} else if (!read_pin(input) && prev_state) {
			write_pin(output, LOW);
			printf("Switch Open\n");
			prev_state = LOW;
		}
	}
}
