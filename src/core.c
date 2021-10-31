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
	// Initialisation of struct calccity
	memset(calccity, 0, sizeof *calccity);

	// Treasure
	calccity->misc[0] = 500000;

	for (int i = 0; i < 4; i++)
		calccity->taxes[i] = 10;

	calccity->month = 1;
	calccity->year = 1900;
	calccity->blinker = 0;

	calccity->disaster = 1;
	calccity->animation = 1;
	calccity->time_speed = 30;


	// Initialisation of struct camera
	memset(camera, 0, sizeof *camera);
	camera->cursor_x = 64;
	camera->cursor_y = 32;


	// Initialisation of struct map
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			// Water
			if ((x * y == 0) || (x == 49 || y == 49))
				map->data[y][x] = 139;
			
			// Shorelines
			

			// Ground
			else
				map->data[y][x] = 48 + rand() % 2;


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
		display_map(calccity, camera, map);

		key = rtc_key();

	}

	// Free timer
	if (t >= 0) timer_stop(t);
}