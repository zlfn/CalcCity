#include <gint/display.h>
#include <gint/keyboard.h>

#include "display.h"


void title_screen(void)
{
	extern const bopti_image_t img_title;
	dclear(C_WHITE);

	dimage(0, 0, &img_title);
	dupdate();
	getkey();
}


void display_map(struct calccity *calccity, struct camera *camera, struct map *map)
{
	extern const bopti_image_t img_large_tileset;
	extern const bopti_image_t img_large_water;

	if (calccity->animation)
		calccity->blinker = (calccity->blinker + 1 ) % 2;
	else
		calccity->blinker = 0;

	dclear(C_WHITE);
	for (int y = camera->y; y <= camera->y + 3; y++)
	{
		for (int x = camera->x; x <= camera->x + 7; x ++)
		{
			// Water
			if (map->data[y][x] == 139) 
				dsubimage(x * 15, y * 15, &img_large_water, 15 * calccity->blinker, 0, 15 * (calccity->blinker + 1), 15, DIMAGE_NONE);
			else
			{
				unsigned tile_id = map->data[y][x];
				unsigned int tile_x = 16 * (tile_id % 10);
                unsigned int tile_y = 16 * (tile_id / 10);

                dsubimage(x * 15, y * 15, &img_large_tileset, tile_x, tile_y, 15, 15, DIMAGE_NONE);
			}
		}
	}
	dupdate();
}
