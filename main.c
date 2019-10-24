#include "main.h"

int GROUND;
int WALL;
bool EXIT = false;

int elapsed_time = 0;


int main(int argv, char **argc)
{
	int code = tb_init();

	/* Check if termbox was initialized. */
	if(code < 0) {
		fprintf(stderr, "termbox init failed, code: %d\n", code);
		return -1;
	}

	tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();

	GROUND = tb_height() - 1;
	WALL = tb_width() - 1;

	pthread_t timer_thread;
	pthread_create(&timer_thread, NULL, timer, NULL);

	Bike bike;
	Bike__init(&bike, 0.0f, 0.0f);

	Linepieces linepieces;
	Linepieces__init(&linepieces);

	/* Quit loop if exit is true. */
	while(!EXIT){
		tb_clear();

		/* Update the simulation. */
		if(elapsed_time % UPDATE_SPEED == 0) {
			/* Handle input. */
			input(&bike, &linepieces);

			Bike__update(&bike, linepieces.x, linepieces.y,
			linepieces.SIZE, GROUND, WALL, GRAVITY, 1000.0f / UPDATE_SPEED);
		}

		/* Draw. */
		if(elapsed_time % DRAW_SPEED == 0) {
			drawBackground();

			Linepieces__draw(&linepieces);
			Bike__draw(&bike);

			/* Draw to screen. */
			tb_present();
		}

		/* Increase time to ensure that timed loops won't
		 * be called twice. */
		elapsed_time++;
	}

	tb_shutdown();

	save_level(&linepieces);

	return 0;
}

void save_level(Linepieces *linepieces)
{
	printf("Save this level by copying the symbols below. \n");

	/* Find max x and y values. */
	int max_x = max(linepieces->y, linepieces->SIZE);
	int max_y = max(linepieces->x, linepieces->SIZE);

	/* Create an empty level. */
	char level [max_y][max_x];
	for(int y = 0; y < max_y; y++)
		for(int x = 0; x < max_x; x++)
			level[y][x] = ' ';

	/* Save all line symbols. */
	for(int i = 0; i < linepieces->SIZE; i++)
		level[linepieces->y[i]][linepieces->x[i]] =
		linepieces->line_symbols[i];

	/* Print level. */
	for(int y = 0; y < max_y; y++){
		for(int x = 0; x < max_x; x++)
			printf("%c", level[y][x]);

		printf("\n");
	}

	printf("\n");
}

int max(int *array, int size)
{
	int max_val = 0;

	for(int i = 0; i < size; i++)
		if(array[i] > max_val)
			max_val = array[i];

	return max_val;
}

void input(Bike *bike, Linepieces *linepieces)
{
	struct tb_event ev;

	/* Update input with a timeout of n ms. */
	tb_peek_event(&ev, 0);

	/* Determine type of input: keyboard or mouse. */
	switch(ev.type) {
		/* Keyboard input. */
		case TB_EVENT_KEY: {
			/* Determine which key was pressed. */
			switch(ev.key) {
				case TB_KEY_ESC: {
					EXIT = true;
					break;
				}

				case TB_KEY_ARROW_LEFT: {
					Bike__accelerate(bike, -0.1f);
					break;
				}

				case TB_KEY_ARROW_RIGHT: {
					Bike__accelerate(bike, 0.1f);
					break;
				}
			}

			break;
		}

		/* Mouse click. */
		case TB_EVENT_MOUSE: {
			Linepieces__add(linepieces, ev.x, ev.y);
			break;
		}
	}
}

void drawBackground()
{
	/* Draw the background. */
	for(int x = 0; x < tb_width(); x++){
		for(int y = 0; y < tb_height(); y++){
			tb_change_cell(x, y, ' ', BACKGROUND_COLOR,
			BACKGROUND_COLOR);
		}
	}
}

void *timer()
{
	/* Needed for nanosleep. */
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 1000000;

	while(!EXIT){
		nanosleep(&tim, &tim2);
		elapsed_time++;

		if(elapsed_time == 160)
			elapsed_time = 0;
	}

	return &EXIT;
}
