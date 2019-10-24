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
	if(direction > 0.0f)
		this->ax += BIKE_ACCELERATION;
	else
		this->ax -= BIKE_ACCELERATION;
}

void Bike__update(Bike *this, int linepiece_x[], int linepiece_y[],
int linepiece_count, int ground, int wall, float gravity, float speed_factor)
{
	/* Change the bike's acceleration according to the update speed. */
	this->ay = gravity / speed_factor;
	this->ax /= speed_factor;

	this->vx += this->ax;

	/* Limit the bike's speed to BIKE_TOP_SPEED. */
	if(this->vx > BIKE_TOP_SPEED) {
		this->vx = BIKE_TOP_SPEED;
		this->ax = 0.0f;
	}

	this->vy += this->ay;
	this->x += this->vx;

	/* If a line exist below the bike, within it's hitbox,
	 * set that line as the bike's ground. */
	for(int i = 0; i < linepiece_count; i++) {
		if(abs(this->x - linepiece_x[i]) < BIKE_WIDTH)
			if(this->y - BIKE_HEIGHT < linepiece_y[i])
				ground = linepiece_y[i];
	}

	/* Prevent the bike from falling through the ground. */
	if(this->y > ground) {
		this->y = ground;
		this->vy = 0.0f;
		this->ay = 0.0f;
	} else {
		this->y += this->vy;
	}

	/* Stop the bike at the walls. */
	if(this->x > wall - BIKE_WIDTH) {
		this->vx = 0.0f;
		this->ax = 0.0f;
		this->x = wall - BIKE_WIDTH;
	}

	if(this->x < 0.0f) {
		this->vx = 0.0f;
		this->ax = 0.0f;
		this->x = 0.0f;
	}
}

void Bike__draw(Bike *this)
{
	int index = 0;

	/* Loop through every character in Bike__sprite
	 * and draw that character. */
	for(int y = 0; y < BIKE_SPRITE_SIZE / BIKE_SPRITE_ROW; y++) {
		for(int x = 0; x < BIKE_SPRITE_ROW; x++) {
			/* Don't draw spaces. */
			if(Bike__sprite[index] != ' ') {
				tb_change_cell(this->x + x,
				this->y - BIKE_SPRITE_SIZE / BIKE_SPRITE_ROW + 1 + y,
				Bike__sprite[index], BIKE_COLOR, BACKGROUND_COLOR);
			}

			index++;
		}
	}
}
