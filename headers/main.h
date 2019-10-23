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

#define UPDATE_SPEED 20 // Must be at least 10
#define DRAW_SPEED 16 // 16 := 60 ~fps

void save_level(Linepieces *linepieces);
int max(int *array, int size);
void input(Bike *bike, Linepieces *linepieces);
void drawBackground();
void *timer();

#endif
