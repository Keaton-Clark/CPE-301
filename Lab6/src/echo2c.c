#include <avr/io.h>
#include <stdio.h>
#include "io.h"

unsigned char U0kbhit() {
	return (unsigned char)uart_available();
}

unsigned char U0getchar() {
	return (unsigned char)uart_read_char();
}

void U0putchar(unsigned char U0pdata) {
	uart_put_char(U0pdata, stdout);
}
