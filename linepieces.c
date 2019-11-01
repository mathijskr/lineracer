#include "headers/linepieces.h"

void Linepieces__init(Linepieces *this)
{
	this->SIZE = 0;
	this->index = 0;
}

void Linepieces__add(Linepieces *this, int x, int y)
{
	/* Append a new line. */
	if(this->SIZE < LINEPIECES_MAX_SIZE) {
		this->x[this->index] = x;
		this->y[this->index] = y;
		this->SIZE++;
		this->index++;
	} else {
		/* Reset the index and add line at the beginning. */
		if(this->index >= LINEPIECES_MAX_SIZE)
			this->index = 0;

		this->x[this->index] = x;
		this->y[this->index] = y;
		this->index++;
	}
}

void Linepieces__draw(Linepieces *this)
{
	for(int i = 0; i < this->SIZE; i++){

		this->line_symbols[i] = '_';

		/* Determine the kind of line symbol according to the
		 * position of the previous line. */
		if(i > 0){
			int delta_x = this->x[i] - this->x[i - 1];
			int delta_y = this->y[i] - this->y[i - 1];

			if(delta_y == 1){
				if(delta_x == 1){
					this->line_symbols[i] = '\\';
				} else if(delta_x == 0){
					this->line_symbols[i] = '|';
				} else if(delta_x == -1){
					this->line_symbols[i] = '/';
				}
			}
		}

		/* Determine the kind of line symbol according to the
		 * position of the next line. */
		if(i < this->SIZE - 1) {
			int delta_x = this->x[i] - this->x[i + 1];
			int delta_y = this->y[i] - this->y[i + 1];

			if(delta_y == 1){
				if(delta_x == 1){
					this->line_symbols[i] = '\\';
				} else if(delta_x == 0){
					this->line_symbols[i] = '|';
				} else if(delta_x == -1){
					this->line_symbols[i] = '/';
				}
			}
		}
	}

	/* Draw all line symbols at the correct coordinates. */
	for(int i = 0; i < this->SIZE; i++)
		tb_change_cell(this->x[i], this->y[i], this->line_symbols[i],
		LINE_COLOR, BACKGROUND_COLOR);
}
