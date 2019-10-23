#ifndef LINEPIECES_H
#define LINEPIECES_H

#include "termbox.h"
#include "constants.h"

#define LINEPIECES_MAX_SIZE 100
#define LINE_COLOR TB_BLUE

typedef struct Linepieces Linepieces;

struct Linepieces {
	int SIZE;
	int index;

	/* The x and y coordinates of a line. */
	int x[LINEPIECES_MAX_SIZE];
	int y[LINEPIECES_MAX_SIZE];

	/* What kind of line: / \ | _ */
	char line_symbols[LINEPIECES_MAX_SIZE];
};

/* Set the SIZE and the index of a linepieces struct to zero.
 * The SIZE indicates the current size of linepieces,
 * the index indicates at which position a new line will be added. */
void Linepieces__init(Linepieces *this);

/* Add a new line at SIZE, or if SIZE is already at the LINEPIECES_MAX_SIZE,
 * reset the index variable and add the line at the index's position. */
void Linepieces__add(Linepieces *this, int x, int y);

/* Draw every line at it's x and y coordinate
 * with the symbol specified in line_symbols. */
void Linepieces__draw(Linepieces *this);

#endif
