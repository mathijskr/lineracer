#ifndef BIKE_H
#define BIKE_H

#include "termbox.h"
#include "constants.h"

#define BIKE_SPRITE_SIZE 10
#define BIKE_SPRITE_ROW 5
#define BIKE_COLOR TB_RED

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
void Bike__draw(Bike *this);

#endif
