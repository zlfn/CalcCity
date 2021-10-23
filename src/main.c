#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/std/stdlib.h>
#include <gint/std/string.h>

#include "calccity.h"

void title_screen(void);
void default_values(struct calccity *current_game, struct camera *camera, struct map *map);


int main(void)
{
	title_screen();

	struct calccity calccity;
	struct camera camera;
	struct map map;
	default_values(&calccity, &camera, &map);

	return 1;
}


void title_screen(void)
{
	extern const bopti_image_t img_title;
	dclear(C_WHITE);

	dimage(0, 0, &img_title);
	dupdate();

	getkey();
}


void default_values(struct calccity *calccity, struct camera *camera, struct map *map)
{
	// Initialisation of struct calccity
	memset(calccity, 0, sizeof *calccity);

	// Treasure
	calccity->misc[0] = 500000;

	for (int i = 0; i < 4; i++)
		calccity->taxes[i] = 10;

	calccity->month = 1;
	calccity->year = 1900;
	calccity->blinker = 0;

	calccity->disaster = true;
	calccity->time_speed = 30;


	// Initialisation of struct camera
	memset(camera, 0, sizeof *camera);
	camera->cursor_x = 64;
	camera->cursor_y = 32;


	// Initialisation of struct map
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
			map->data[y][x] = 48 + rand() % 2;
	}

}