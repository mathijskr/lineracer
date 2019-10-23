#ifndef BIKE_H
#define BIKE_H

#include "termbox.h"
#include "constants.h"

#define BIKE_SPRITE_SIZE 10
#define BIKE_SPRITE_ROW 5
#define BIKE_COLOR TB_RED
#define BIKE_ACCELERATION  0.1f
#define BIKE_TOP_SPEED 10.0f

typedef struct Bike Bike;

struct Bike {
	float x, y;
	float vx, vy;
	float ax, ay;
};

static const char Bike__sprite[BIKE_SPRITE_SIZE] = {	'/','-','-','|','>',
							'*',' ',' ',' ','*'
};


void Bike__init(Bike *this, float x, float y);

void Bike__accelerate(Bike *this, float direction);
void Bike__update(Bike *this, int ground, float gravity, float speed_factor);

void Bike__draw(Bike *this);

#endif
