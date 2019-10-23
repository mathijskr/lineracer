#include "headers/linepieces.h"

void Linepieces__init(Linepieces *this)
{
	this->SIZE = 0;
}

void Linepieces__add(Linepieces *this, float x, float y)
{
	if(this->SIZE < LINEPIECES_MAX_SIZE) {
		this->x[this->SIZE] = x;
		this->y[this->SIZE] = y;
		this->SIZE++;
	}
}

void Linepieces__draw(Linepieces *this)
{
	for(int i = 0; i < this->SIZE; i++) {
		tb_change_cell(this->x[i], this->y[i], '_', LINE_COLOR, BACKGROUND_COLOR);
	}
}
