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


void display_large_map(struct calccity *calccity, struct camera *camera, struct map *map)
{
	extern const bopti_image_t img_large_tileset;
	extern const bopti_image_t img_large_water;

	dclear(C_WHITE);

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 8; x ++)
		{
			int cam_x = x + camera->x, cam_y = y + camera->y;
			// Water
			if (cam_y > 49 || cam_x > 49 || map->data[cam_y][cam_x] == 139) 
				dsubimage(3 + x * 15, y * 15, &img_large_water, 15 * calccity->blinker, 0, 15 * (calccity->blinker + 1), 15, DIMAGE_NONE);
			else
			{
				unsigned tile_id = map->data[cam_y][cam_x];
				unsigned int tile_x = 15 * (tile_id % 10);
                unsigned int tile_y = 15 * (tile_id / 10);

                dsubimage(3 + x * 15, y * 15, &img_large_tileset, tile_x, tile_y, 15, 15, DIMAGE_NONE);
			}
		}
	}

}


void display_around(struct calccity *calccity, struct camera *camera)
{
	extern const bopti_image_t img_fn_keys;

	// Functions keys
	dimage(3, 57, &img_fn_keys);

	// Frame around screen
	dline(3, 0, 123, 0, C_BLACK);
	dline(3, 56, 123, 56, C_BLACK);
	dline(3, 0, 3, 56, C_BLACK);
	dline(123, 0, 123, 56, C_BLACK);

	// Date in the top-left corner
	dprint_opt(4, 1, C_BLACK, C_WHITE, DTEXT_LEFT, DTEXT_TOP, "%d-%d", calccity->month, calccity->year);
	
	// Cursor
	drect_border(8 * camera->cursor_x + 3, 8 * camera->cursor_y, 8 * camera->cursor_x + 11, 8 * camera->cursor_y + 8, C_WHITE, 1, C_BLACK);
	dline(8 * camera->cursor_x + 6, 8 * camera->cursor_y + 4, 8 * camera->cursor_x + 8, 8 * camera->cursor_y + 4, C_BLACK);
	dline(8 * camera->cursor_x + 7, 8 * camera->cursor_y + 3, 8 * camera->cursor_x + 7, 8 * camera->cursor_y + 5, C_BLACK);


	dupdate();
}

