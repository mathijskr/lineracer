#include "headers/linepieces.h"

void Linepieces__init(Linepieces *this)
{
	this->SIZE = 0;
	this->index = 0;
}

void Linepieces__add(Linepieces *this, int x, int y)
{
	if(this->SIZE < LINEPIECES_MAX_SIZE) {
		this->x[this->index] = x;
		this->y[this->index] = y;
		this->SIZE++;
		this->index++;
	} else {
		if(this->index >= LINEPIECES_MAX_SIZE)
			this->index = 0;
		this->x[this->index] = x;
		this->y[this->index] = y;
		this->index++;
	}
}

void Linepieces__draw(Linepieces *this)
{
	char line_symbols[this->SIZE];

	for(int i = 0; i < this->SIZE; i++){

		line_symbols[i] = '_';

		if(i > 0){
			int delta_x = this->x[i] - this->x[i - 1];
			int delta_y = this->y[i] - this->y[i - 1];

			if(delta_y == 1){
				if(delta_x == 1){
					line_symbols[i] = '\\';
				} else if(delta_x == 0){
					line_symbols[i] = '|';
				} else if(delta_x == -1){
					line_symbols[i] = '/';
				}
			}
		}

		if(i < this->SIZE - 1) {
			int delta_x = this->x[i] - this->x[i + 1];
			int delta_y = this->y[i] - this->y[i + 1];

			if(delta_y == 1){
				if(delta_x == 1){
					line_symbols[i] = '/';
				} else if(delta_x == 0){
					line_symbols[i] = '|';
				} else if(delta_x == -1){
					line_symbols[i] = '\\';
				}
			}
		}
	}

	for(int i = 0; i < this->SIZE; i++)
		tb_change_cell(this->x[i], this->y[i], line_symbols[i], LINE_COLOR, BACKGROUND_COLOR);
}
