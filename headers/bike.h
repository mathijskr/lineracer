#ifndef BIKE_H
#define BIKE_H

#include <stdlib.h>

#include "termbox.h"
#include "constants.h"

#define BIKE_SPRITE_SIZE 10
#define BIKE_SPRITE_ROW 5
#define BIKE_COLOR TB_RED
#define BIKE_ACCELERATION 0.1f
#define BIKE_TOP_SPEED 10.0f
#define BIKE_WIDTH 5.0f
#define BIKE_HEIGHT 2.0f

typedef struct Bike Bike;

struct Bike {
	float x, y;
	float vx, vy;
	float ax, ay;
};

static const char Bike__sprite[BIKE_SPRITE_SIZE] = {	'/','-','-','|','>',
							'*',' ',' ',' ','*'
};


/* Create a new bike at position x, y.
 * Set it's velocity and acceleration to zero. */
void Bike__init(Bike *this, float x, float y);

/* Increase the bike's acceleration with the value of BIKE_ACCELERATION.
 * Specify in which direction the bike should by accelerating by either
 * passing a positive or negative direction. */
void Bike__accelerate(Bike *this, float direction);

/* Update a bike's acceleration, position and velocity
 * and prevent the bike from falling throug a line or the ground. */
void Bike__update(Bike *this, int *linepiece_x, int *linepiece_y,
int linepiece_count, int ground, int wall, float gravity, float speed_factor);

/* Draw Bike__sprite at the bike's position. */
void Bike__draw(Bike *this);

#endif
