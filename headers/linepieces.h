#ifndef LINEPIECES_H
#define LINEPIECES_H

#include "termbox.h"
#include "constants.h"

#define LINEPIECES_MAX_SIZE 50
#define LINE_COLOR TB_BLUE

typedef struct Linepieces Linepieces;

struct Linepieces {
	int SIZE;

	float x[LINEPIECES_MAX_SIZE];
	float y[LINEPIECES_MAX_SIZE];
};

void Linepieces__init(Linepieces *this);

void Linepieces__add(Linepieces *this, float x, float y);

void Linepieces__draw(Linepieces *this);

#endif
