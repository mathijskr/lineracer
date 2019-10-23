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

void Bike__accelerate(Bike *this, float direction)
{
	this->ax += direction * BIKE_ACCELERATION;
}

void Bike__update(Bike *this, int ground, float gravity, float speed_factor)
{
	this->ay = gravity / speed_factor;
	this->ax /= speed_factor;

	this->vx += this->ax;

	if(this->vx > BIKE_TOP_SPEED) {
		this->vx = BIKE_TOP_SPEED;
		this->ax = 0.0f;
	}

	this->vy += this->ay;
	this->x += this->vx;
	this->y += this->vy;

	if(this->y > ground)
		this->y = ground;
}

void Bike__draw(Bike *this)
{
	int index = 0;

	for(int y = 0; y < BIKE_SPRITE_SIZE / BIKE_SPRITE_ROW; y++)
		for(int x = 0; x < BIKE_SPRITE_ROW; x++)
			tb_change_cell(this->x + x, this->y - BIKE_SPRITE_SIZE / BIKE_SPRITE_ROW + 1 + y, Bike__sprite[index++], BIKE_COLOR, BACKGROUND_COLOR);
}
