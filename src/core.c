#include <gint/keyboard.h>
#include <gint/std/stdlib.h>
#include <gint/std/string.h>
#include <gint/timer.h>
#include <gint/clock.h>

#include "core.h"


int callback_tick(volatile int *tick)
{
	*tick = 1;
	return TIMER_CONTINUE;
}



void default_values(struct calccity *calccity, struct camera *camera, struct map *map)
{
	srand(20211104);

	// Initialisation of struct calccity
	memset(calccity, 0, sizeof *calccity);

	// Treasure
	calccity->misc[0] = 5000;

	for (int i = 0; i < 4; i++)
	{
		calccity->taxes[i] = 10;
		calccity->funds[i] = 100;
	}

	calccity->month = 1;
	calccity->year = 1900;
	calccity->blinker = 0;

	calccity->disaster = 1;
	calccity->animation = 1;
	calccity->time_speed = 5100;


	// Initialisation of struct camera
	memset(camera, 0, sizeof *camera);
	camera->cursor_x = 2;
	camera->cursor_y = 2;


	// Initialisation of struct map
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			// Water
			if ((x * y == 0) || (x == 49 || y == 49))
				map->data[y][x] = 139;
			// Ground
			else
				map->data[y][x] = 48 + rand() % 2;
			
			// Shorelines

			switch (y)
			{
				case 1:
					switch (x)
					{
						case 1:
							map->data[y][x] = 110;
							break;

						case 48:
							map->data[y][x] = 112;
							break;

						default:
							if (x != 0 && x != 49) map->data[y][x] = 111;
							break;
					}
					break;
			
				case 48:
					switch (x)
					{
						case 1:
							map->data[y][x] = 130;
							break;

						case 48:
							map->data[y][x] = 132;
							break;

						default:
							if (x != 0 && x != 49) map->data[y][x] = 131;
							break;
					}
					break;

				default:
					if (y != 0 && y != 49)
					{
						if (x == 1) map->data[y][x] = 120;
						if (x == 48) map->data[y][x] = 122;
					}
			}
		}
	}

}


int rtc_key(void)
{
	int opt = GETKEY_DEFAULT & ~GETKEY_MOD_SHIFT & ~GETKEY_MOD_ALPHA & ~GETKEY_REP_ARROWS;
	int timeout = 1;
		
	key_event_t ev = getkey_opt(opt, &timeout);
	if(ev.type == KEYEV_NONE) return 0;
		
	return ev.key;
}


void next_step(struct calccity *calccity)
{
	calccity->tick += ENGINE_TICK;

	// In-game animation
	if (calccity->animation && !(calccity->tick % 1000))
		calccity->blinker = (calccity->blinker + 1 ) % 2;

	// In-game time
	if (!(calccity->tick % calccity->time_speed))
	{
		calccity->month ++;
		if (calccity->month > 12)
		{
			calccity->month = 1;
			calccity->year ++;
		}
	}
}


void main_loop(struct calccity *calccity, struct camera *camera, struct map *map)
{
	// Timer initialisation
	static volatile int tick = 1;
	int t = timer_configure(TIMER_ANY, ENGINE_TICK*1000, GINT_CALL(callback_tick, &tick));
	if (t >= 0) timer_start(t);

	int end = 0, key = 0;

	//int build_mode = 0;

	while (!end)
	{
		// Real-time clock system
        while (!tick) sleep();
        tick = 0;

        next_step(calccity);

        // Display map
		display_large_map(calccity, camera, map);
		display_around(calccity, camera);

		// Get and manage input
		key = rtc_key();
		keyboard_managment(calccity, camera, key);

		// Open the menu
		switch (calccity->menu)
		{	
			// Tax and funds
			case 4:
				menu_4(calccity);
				break;

			case 5:
				menu_5(calccity);
				break;

			// Options
			case 6:
				end = menu_6(calccity);
				break;
		}
		calccity->menu = 0;
	}

	// Free timer
	if (t >= 0) timer_stop(t);
}


void keyboard_managment(struct calccity *calccity, struct camera *camera, const int key)
{
	switch (key)
	{
		case KEY_UP:
			if (camera->cursor_y > 0) camera->cursor_y --;
			else if (camera->y > 0) camera->y --;
			break;
		
		case KEY_RIGHT:
			if (camera->cursor_x < 14) camera->cursor_x ++;
			else if (camera->x < 42) camera->x ++;
			break;

		case KEY_DOWN:
			if (camera->cursor_y < 6) camera->cursor_y ++;
			else if (camera->y < 46) camera->y ++;
			break;

		case KEY_LEFT:
			if (camera->cursor_x > 0) camera->cursor_x --;
			else if (camera->x > 0) camera->x --;
			break;


		case KEY_F1:
			calccity->menu = 1;
			break;

		case KEY_F2:
			calccity->menu = 2;
			break;

		case KEY_F3:
			calccity->menu = 3;
			break;

		case KEY_F4:
			calccity->menu = 4;
			break;

		case KEY_F5:
			calccity->menu = 5;
			break;

		case KEY_F6:
			calccity->menu = 6;
			break;
	}
}