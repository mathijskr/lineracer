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

	tb_select_input_mode(TB_INPUT_ESC);
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();

	GROUND = tb_height() - 1;
	WALL = tb_width() - 1;

	pthread_t timer_thread;
	pthread_create(&timer_thread, NULL, timer, NULL);

	Bike bike;
	Bike__init(&bike, 0.0f, 0.0f);

	/* Quit loop if exit is true. */
	while(!EXIT){
		tb_clear();

		/* Update the simulation. */
		if(elapsed_time % UPDATE_SPEED == 0) {
			/* Handle input. */
			input(&bike);

			Bike__update(&bike, GROUND, GRAVITY, 1000.0f / UPDATE_SPEED);
		}

		/* Draw. */
		if(elapsed_time % DRAW_SPEED == 0) {
			drawBackground();

			Bike__draw(&bike);

			/* Draw to screen. */
			tb_present();
		}

		/* Increase time to ensure that timed loops won't be called twice. */
		elapsed_time++;
	}

	tb_shutdown();
	return 0;
}

void input(Bike *bike)
{
	struct tb_event ev;

	/* Update input with a timeout of n ms. */
	tb_peek_event(&ev, 0);

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
