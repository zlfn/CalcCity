#include <gint/display.h>
#include <gint/keyboard.h>
#include <math.h>

#include "display.h"


void title_screen(void)
{
	extern const bopti_image_t img_title;
	dclear(C_WHITE);

	dimage(0, 0, &img_title);
	dupdate();
	getkey();
}


void display_main(struct calccity *calccity, struct camera *camera, struct map *map, const int disp_cursor)
{
    // Display map
    if (camera->zoom == 0)
	{
		display_large_map(calccity, camera, map);
		display_around(calccity, camera, disp_cursor);
	}
	else
	{
		display_mini_map(camera, map);
		display_around(calccity, camera, 0);
	}
}


void display_large_map(struct calccity *calccity, struct camera *camera, struct map *map)
{
	extern const bopti_image_t img_large_tileset;
	extern const bopti_image_t img_large_water;
	extern const bopti_image_t img_alerts;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 8; x ++)
		{
			int cam_x = x + camera->x, cam_y = y + camera->y;

			// Water
			if (cam_y > 49 || cam_x > 49 || map->data[cam_y][cam_x] == 139) 
				dsubimage(3 + x * 15, y * 15, &img_large_water, 15 * calccity->blinker_water, 0, 15 * (calccity->blinker_water + 1), 15, DIMAGE_NONE);
			else
			{
				unsigned tile_id = map->data[cam_y][cam_x];
				unsigned int tile_x = 15 * (tile_id % 10);
				unsigned int tile_y = 15 * (tile_id / 10);
				
				dsubimage(3 + x * 15, y * 15, &img_large_tileset, tile_x, tile_y, 15, 15, DIMAGE_NONE);

				// Visual alerts in case of low energy and low water
				if (calccity->animation && map->id[cam_y][cam_x] > 2 && map->data[cam_y][cam_x] < 79)
				{
					// Low water
					if (calccity->stat[17] - calccity->stat[16] < 0 && calccity->blinker_alert == 0)
						dsubimage(3 + x * 15, y * 15, &img_alerts, 15, 0, 15, 15, DIMAGE_NONE);

					// Low energy
					if (calccity->stat[19] - calccity->stat[18] < 0 && calccity->blinker_alert == 1)
						dsubimage(3 + x * 15, y * 15, &img_alerts, 0, 0, 15, 15, DIMAGE_NONE);
				}
			}
		}
	}
}


void display_mini_map(struct camera *camera, struct map *map)
{
	extern const bopti_image_t img_mini_tileset;

	for (int y = 0; y < 7; y ++)
	{
		for (int x = 0; x < 15; x ++)
		{
			int cam_x = x + camera->x, cam_y = y + camera->y;

			unsigned tile_id = map->data[cam_y][cam_x];
			unsigned int tile_x = 8 * (tile_id % 10);
			unsigned int tile_y = 8 * (tile_id / 10);

			dsubimage(3 + x * 8, y * 8, &img_mini_tileset, tile_x, tile_y, 8, 8, DIMAGE_NONE);
		}
	}
}

void display_around(struct calccity *calccity, struct camera *camera, const int disp_cursor)
{
	extern const bopti_image_t img_fn_keys;

	// Date in the top-left corner
	dprint_opt(5, 1, C_BLACK, C_WHITE, DTEXT_LEFT, DTEXT_TOP, "%d-%d", calccity->month, calccity->year);
	
	// Cursor
	if (disp_cursor)
	{

		int offset_x = floor(camera->cursor_x / 2);
		int offset_y = floor(camera->cursor_y / 2);

		drect_border(8 * camera->cursor_x - offset_x + 3, 8 * camera->cursor_y - offset_y, 8 * (camera->cursor_x + 1) - offset_x + 3, 8 * (camera->cursor_y + 1) - offset_y , C_WHITE, 1, C_BLACK);

		dline(8 * camera->cursor_x - offset_x + 6, 8 * camera->cursor_y - offset_y + 4, 8 * camera->cursor_x - offset_x + 8, 8 * camera->cursor_y - offset_y + 4, C_BLACK);
		dline(8 * camera->cursor_x - offset_x + 7, 8 * camera->cursor_y - offset_y + 3, 8 * camera->cursor_x - offset_x + 7, 8 * camera->cursor_y - offset_y + 5, C_BLACK);		

		if (camera->cursor_size[0] > 8 && camera->cursor_size[1] > 8)
		{
			unsigned short x = camera->cursor_size[0] * floor(camera->cursor_x / (floor(camera->cursor_size[0] / 8) + 1)) + 3;
			unsigned short y = camera->cursor_size[1] * floor(camera->cursor_y / (floor(camera->cursor_size[1] / 8) + 1));
			drect_border(x, y, x + camera->cursor_size[0], y + camera->cursor_size[1], C_NONE, 1, C_BLACK);
		}

	}

	// Functions keys
	dimage(3, 57, &img_fn_keys);

	// Frame around screen
	dline(3, 0, 123, 0, C_BLACK);
	dline(3, 56, 123, 56, C_BLACK);
	dline(3, 0, 3, 56, C_BLACK);
	dline(123, 0, 123, 56, C_BLACK);
}


void display_message(char* message)
{
	dclear(C_WHITE);

	drect(0, 0, 127, 6, C_BLACK);
	dhline(0, C_BLACK);
	dhline(63, C_BLACK);
	dvline(0, C_BLACK);
	dvline(127, C_BLACK);
	dtext(42, 1, C_WHITE, "MESSAGE");

	int total_offset = 0;
    for (int i = 0; i < 5; i ++)
    {
        dtext_opt(3, 7 * i + 8, C_BLACK, C_WHITE, 0, 0, message + total_offset, 20);
        
        int offset = 0;
        while (message[total_offset + offset] != '\0') offset += 1;

        if (!offset) break;
        else if (offset > 20) total_offset += 20;
        else total_offset += offset;
    }

    dupdate();

    int opt = GETKEY_DEFAULT & ~GETKEY_MOD_SHIFT & ~GETKEY_MOD_ALPHA & ~GETKEY_REP_ARROWS;
	int timeout = 0;
		
    int key = 0;
    while (key != KEY_ALPHA)
    	key = getkey_opt(opt, &timeout).key;
}

