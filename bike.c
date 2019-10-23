#include "headers/bike.h"

void Bike__init(Bike *this, float x, float y)
{
	this->x = x;
	this->y = y;
	this->vx = 0.0f;
	this->vy = 0.0f;
	this->ax = 0.0f;
	this->ay = 0.0f;
}

void Bike__draw(Bike *this)
{
	int index = 0;

	for(int y = 0; y < BIKE_SPRITE_SIZE / BIKE_SPRITE_ROW; y++)
		for(int x = 0; x < BIKE_SPRITE_ROW; x++)
			tb_change_cell(this->x + x, this->y + y, Bike__sprite[index++], BIKE_COLOR, BACKGROUND_COLOR);
}
