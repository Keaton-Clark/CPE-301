#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "matrix.h"
#include "sevenseg.h"

#define MATRIX_ROWS 4
#define MATRIX_COLS 3

int main () {
	pin_t matrix_rows[MATRIX_ROWS] = {
		[0] = new_pin(22),
		[1] = new_pin(24),
		[2] = new_pin(26),
		[3] = new_pin(28),
	};
	pin_t matrix_cols[MATRIX_COLS] = {
		[0] = new_pin(23),
		[1] = new_pin(25),
		[2] = new_pin(27),
	};
	char matrix_lookup[MATRIX_ROWS * MATRIX_COLS] = {
		'1', '2', '3',
		'4', '5', '6',
		'7', '8', '9',
		'\n', '0', -1
	};
	pin_t sevenseg_dig[4] = {
		[0] = new_pin(2),
		[1] = new_pin(3),
		[2] = new_pin(4),
		[3] = new_pin(5),
	};
	pin_t sevenseg_seg[7] = {
		[0] = new_pin(30),
		[1] = new_pin(31),
		[2] = new_pin(32),
		[3] = new_pin(33),
		[4] = new_pin(34),
		[5] = new_pin(35),
		[6] = new_pin(36),
	};
	four_dig_seven_seg_t sevenseg = init_four_dig_seven_seg(sevenseg_dig, sevenseg_seg);
	matrix_t matrix = init_matrix(MATRIX_ROWS, matrix_rows, MATRIX_COLS, matrix_cols, matrix_lookup);
	char key_press;
	char display[4] = {0, 0, 0, 0}; 
	for(;;) {
		for (int i = 3; i >= 0;) {
			key_press = read_matrix(matrix);
			if (key_press != 0) {
				display[i] = key_press;
				i--;
			}
			four_dig_seven_seg_write(&sevenseg, display);
			while (key_press == read_matrix(matrix)) { // Wait for the keypress to be un-pressed. Update while delaying
				four_dig_seven_seg_update(sevenseg);
			}
			_delay_ms(10); // Little delay because reasons
		}
		for (int i = 0; i < 500; ++i) { // Delay but continue to update while delaying
			four_dig_seven_seg_update(sevenseg);
		}
		memset(display, 0, 4);
		four_dig_seven_seg_write(&sevenseg, display);
		four_dig_seven_seg_update(sevenseg);
	}
}
