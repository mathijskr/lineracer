#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "termbox.h"

#include "constants.h"
#include "bike.h"
#include "linepieces.h"

#define UPDATE_SPEED 20 /* Must be at least 10 */
#define DRAW_SPEED 16 /* 16 := 60 ~fps */

/* Print the user's drawing to stdout. */
void save_level(Linepieces *linepieces);

/* Return the max value of an integer from an array. */
int max(int *array, int size);

/* Handle the user's input. If the user presses a mouse key,
 * a new line will be added to the linepieces.
 * If the user uses the horizontal arrow keys,
 * the bike will accelerate horizontally. */
void input(Bike *bike, Linepieces *linepieces);

/* Draw a space character with a color that is specified by BACKGROUND_COLOR
 * at all possible screen coordinates. */
void drawBackground();

/* Increase the elapsed_time variable every mili second. */
void *timer();

#endif
