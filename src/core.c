#include <gint/keyboard.h>
#include <gint/display.h>
#include <gint/std/string.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "core.h"


int callback_tick(volatile int *tick)
{
	*tick = 1;
	return TIMER_CONTINUE;
}



void default_values(struct calccity *calccity, struct camera *camera, struct map *map)
{
	srand(clock());

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

	calccity->disaster = 1;
	calccity->animation = 1;
	calccity->time_speed = 5100;


	// Initialisation of struct camera
	memset(camera, 0, sizeof *camera);
	camera->cursor_x = 2;
	camera->cursor_y = 2;
	camera->cursor_size[0] = 8;
	camera->cursor_size[1] = 8;


	// Initialisation of struct map
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			// Water
			if ((x * y == 0) || (x == 49 || y == 49))
			{
				map->data[y][x] = 127;
				map->id[y][x] = 1;
			}
			
			// Ground
			else
			{
				map->data[y][x] = 125 + rand() % 2;
				map->id[y][x] = 0;
			}	
		}
	}

	for (int y = 0; y < 50; y ++)
	{
		for (int x = 0; x < 50; x ++)
			check(map, x, y);
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


void next_step(struct calccity *calccity, struct map *map)
{
	calccity->tick += ENGINE_TICK;

	// In-game animation
	if (calccity->animation && !(calccity->tick % 1000))
	{
		calccity->blinker_water = (calccity->blinker_water + 1 ) % 2;
		calccity->blinker_alert = (calccity->blinker_alert + 1) % 3;
	}

	// In-game time
	if (!(calccity->tick % calccity->time_speed))
	{
		calccity->month ++;
		
		if (calccity->month > 12)
		{
			update_stat(calccity, map);
			end_year(calccity);
			calccity->month = 1;
			calccity->year ++;

			if (calccity->disaster)
			{
				int random_event = rand() % 10000;
				// Firehazard
				if (calccity->stat[7] > 1000 && random_event == 0)
				{
					display_message("UN INCENDIE A RAVAGE VOTRE VILLE.");
					disaster(calccity, map, calccity->stat[7]);
					update_stat(calccity, map);
				}

				// Nuclear disaster
				if (calccity->stat[8] >= 1 && random_event == 1)
				{
					display_message("UN ACCIDENT NUCLEAIRE A RAVAGE VOTRE VILLE.");
					disaster(calccity, map, calccity->stat[8] * 100);
					update_stat(calccity, map);
				}

				// Earthquake
				if (random_event == 2)
				{
					display_message("UN TREMBLEMENT DE TERRE A RAVAGE VOTRE VILLE.");
					disaster(calccity, map, rand() % 10);
					update_stat(calccity, map);
				}

				// Treasure
				if (calccity->misc[0] > 1000 && random_event == 3)
				{
					if (rand() % 2)
					{
						display_message("DES INVESTISSEMENT AUDACIEUX VOUS ONT RAPPORTES 1000$ !");
						calccity->misc[0] += 1000;
					}
					else
					{
						display_message("DES INVESTISSEMENT FOIREUX VOUS ONT FAIT PERDRE 1000$.");
						calccity->misc[0] -= 1000;
					}
				}
			}
		}
	}

	// No money
	if (calccity->misc[0] == 0)
	{
		display_message("DES MECENES PRIVES VOUS ONT FAIT UN DON DE 1000$.");
		calccity->misc[0] += 1000;
	}
}


void main_loop(struct calccity *calccity, struct camera *camera, struct map *map)
{
	// Timer initialisation
	static volatile int tick = 1;
	int t = timer_configure(TIMER_ANY, ENGINE_TICK*1000, GINT_CALL(callback_tick, &tick));
	if (t >= 0) timer_start(t);

	struct building building = {0};
	int end = 0, key = 0, build_mode = -1;

	while (!end)
	{
		// Real-time clock system
        while (!tick) sleep();
        tick = 0;

        if (build_mode < 0) next_step(calccity, map);
        
        dclear(C_WHITE);
        display_main(calccity, camera, map, 1);
        if (build_mode >= 0)
        {
        	char building_data[50];
        	sprintf(building_data, "%s:%d$", building.name, building.cost);
        	int width;
        	dsize(building_data, NULL, &width, NULL);
        	drect(4, 6, 5 + width, 11, C_WHITE);
        	dprint_opt(5, 7, C_BLACK, C_WHITE, DTEXT_LEFT, DTEXT_TOP, building_data);
    	}
        dupdate();

		// Get and manage input
		key = rtc_key();
		keyboard_managment(camera, key, build_mode);

		// Menu gestion
		switch (key)
		{
			case KEY_F1: case KEY_F2:
				camera->zoom = 0;
				exit_build_mode(camera, &build_mode);

				if (key == KEY_F1) building = menu_12(calccity, camera, map, &build_mode, 1);
				if (key == KEY_F2) building = menu_12(calccity, camera, map, &build_mode, 2);
				if (build_mode >= 0)
				{
					camera->cursor_size[0] = building.size[0] * 15;
					camera->cursor_size[1] = building.size[1] * 15;
				}
				break;

			case KEY_F4:
				menu_4(calccity);
				update_stat(calccity, map);
				break;

			case KEY_F5:
				menu_5(calccity);
				break;

			case KEY_F6:
				end = menu_6(calccity);
				break;
		}

		if (build_mode >= 0)
		{	
			if (camera->display_name)
				camera->display_name = 0;

			// Build annulation
			if (key == KEY_ALPHA)
				exit_build_mode(camera, &build_mode);

			// Build validation
			if (key == KEY_SHIFT)
			{
				unsigned short loc_x = building.size[0] * floor(camera->x + camera->cursor_x / (floor(camera->cursor_size[0] / 8) + 1));
				unsigned short loc_y = building.size[1] * floor(camera->y + camera->cursor_y / (floor(camera->cursor_size[1] / 8) + 1));
				unsigned char index = 0;

				if (can_build(calccity, map, &building, loc_x, loc_y, &index))
				{
					// Large buildings gestion
					if (build_mode == 5 || build_mode == 8 || build_mode == 11 || build_mode == 27 || build_mode == 28 || build_mode == 29)
					{
						building = large_building(map, &build_mode, &loc_x, &loc_y);
						for (int y = loc_y; y < loc_y + building.size[1]; y ++)
						{
							for (int x = loc_x; x < loc_x + building.size[0]; x ++)
								map->id[y][x] = 0;
						}
						update_stat(calccity, map);
					}
					
					// Destruction
					if (map->id[loc_y][loc_x] != 1 && build_mode == 0)
						destruction(map, loc_x, loc_y);

					// Other buildings
					else
					{
						for (int y = loc_y; y < loc_y + building.size[1]; y ++)
						{
							for (int x = loc_x; x < loc_x + building.size[0]; x ++)
							{
								map->data[y][x] = building.id[index];
								map->id[y][x] = -1;
								index ++;
							}
						}
						map->id[loc_y][loc_x] = build_mode;
					}
					calccity->misc[0] -= building.cost;
					update_stat(calccity, map);
				}
			}

		}
	}
	// Exit build mode
	if (build_mode != -1)
		exit_build_mode(camera, &build_mode);

	// Free timer
	if (t >= 0) timer_stop(t);
}


void keyboard_managment(struct camera *camera, const int key, const int build_mode)
{
	switch (key)
	{
		case KEY_UP:
			if (!camera->zoom && camera->cursor_y > 0) camera->cursor_y --;
			else if (camera->y > 0) camera->y --;
			break;
		
		case KEY_RIGHT:
			if (camera->cursor_x < 14) camera->cursor_x ++;
			else
			{
				if (!camera->zoom && camera->x < 42) camera->x ++;
				if (camera->zoom && camera->x < 35) camera->x ++;
			}
			break;

		case KEY_DOWN:
			if (camera->cursor_y < 6) camera->cursor_y ++;
			else
			{
				if (!camera->zoom && camera->y < 46) camera->y ++;
				if (camera->zoom && camera->y < 43) camera->y ++;
			}
			break;

		case KEY_LEFT:
			if (!camera->zoom && camera->cursor_x > 0) camera->cursor_x --;
			else if (camera->x > 0) camera->x --;
			break;

		case KEY_PLUS:
			camera->zoom = 0;
			break;

		case KEY_MINUS:
			if (build_mode == -1)
			{
				if (camera->x > 35) camera->x = 35;
				if (camera->y > 43) camera->y = 43;
				camera->zoom = 1;
				camera->display_name = 0;
			}
			break;

		case KEY_OPTN:
			if (!camera->zoom)
				camera->display_name = (camera->display_name + 1) % 2;
			break;
	}
}


bool can_build(struct calccity *calccity, struct map *map, struct building *building, const unsigned short loc_x, const unsigned short loc_y, unsigned char *index)
{

	// Not enougth money
	if (calccity->misc[0] < building->cost)
	{
		display_message("VOUS N'AVEZ PAS ASSEZ D'ARGENT POUR CONSTRUIRE.");
		return false;
	}

	// harbor's orientation
	if (building->id[0] == 62)
	{
		*index = check_harbor(map, loc_x, loc_y);
		if (*index == 4)
		{
			display_message("VOUS DEVEZ CONSTUIRE LES PORTS A PROXIMITE DE L'EAU");
			return false;
		}
	}

	for (int y = loc_y; y < loc_y + building->size[1]; y ++)
	{
		for (int x = loc_x; x < loc_x + building->size[0]; x ++)
		{
			// Build on water
			if (map->id[y][x] == 1 && building->id[0] != 110)
			{
				display_message("VOUS NE POUVEZ PAS CONSTRUIRE SUR L'EAU.");
				return false;
			}

			// Build on another building
			if (map->id[y][x] != 0 && building->id[0] != 110)
			{
				display_message("VOUS NE POUVEZ PAS CONSTRUIRE SUR BATIMENT EXISTANT.");
				return false;
			}

			// Build dirt on dirt or water on water
			if ((building->id[0] == 110 && map->id[y][x] == 0) || (building->id[0] == 127 && map->id[y][x] == 1))
				return false;
		}
	}

	return true;
}


void exit_build_mode(struct camera *camera, int *build_mode)
{
	*build_mode = -1;
	camera->cursor_size[0] = 8;
	camera->cursor_size[1] = 8;
}


struct building large_building(struct map *map, int *build_mode, short unsigned int *loc_x, short unsigned int *loc_y)
{
	extern const struct building buildings[42];
	const short unsigned int Y[16] = {*loc_y - 1, *loc_y - 1, *loc_y, *loc_y, *loc_y - 1, *loc_y - 1, *loc_y, *loc_y, *loc_y, *loc_y, *loc_y + 1, *loc_y + 1, *loc_y, *loc_y, *loc_y + 1, *loc_y + 1};
	const short unsigned int X[16] = {*loc_x - 1, *loc_x, *loc_x - 1, *loc_x, *loc_x, *loc_x + 1, *loc_x, *loc_x + 1, *loc_x - 1, *loc_x, *loc_x - 1, *loc_x, *loc_x, *loc_x + 1, *loc_x, *loc_x + 1};
	
	for (int i = 0; i < 4; i ++)
	{
		int check = 0;
		for (int j = 0; j < 4; j ++)
		{
			short unsigned int y = Y[4 * i + j];
			short unsigned int x = X[4 * i + j];
			if (map->id[y][x] == *build_mode) check ++;
		}

		if (check == 3)
		{
			*loc_x = X[4 * i];
			*loc_y = Y[4 * i];

			switch (*build_mode)
			{
				case 5:
					*build_mode = 35;
					break;
				
				case 8:
					*build_mode = 36;
					break;
				
				case 11:
					*build_mode = 37;
					break;
				
				case 27:
					*build_mode = 38;
					break;
				
				case 28:
					*build_mode = 39;
					break;

				case 29:
					*build_mode = 40;
					break;
			}
		}
	}
	return buildings[*build_mode];
}


void update_stat(struct calccity *calccity, struct map *map)
{	
	extern const struct building buildings[42];

	// Reset stat
	for (int i = 0; i < 23; i ++)
		calccity->stat[i] = 0;

	// Buildings stats
	for (int y = 0; y < 50; y ++)
	{
		for (int x = 0; x < 50; x ++)
		{
			// Checking shorelines, roads and railways
			check(map, x, y);

			// Update stat
			if (map->id[y][x] > 1)
			{
				struct building building = buildings[map->id[y][x]];

				for (int i = 0; i < 23; i ++)
				{
					switch (i)
					{
						// TAXES : commercial & work
						case 4: case 10:
							calccity->stat[i] += building.stat[i] + building.taxes[0] * calccity->taxes[1];
							break;

						// TAXES : industrial & production
						case 11: case 12:
							calccity->stat[i] += building.stat[i] + building.taxes[1] * calccity->taxes[2];
							break;

						// TAXES : import & export
						case 13: case 14:
							calccity->stat[i] += building.stat[i] + building.taxes[2] * calccity->taxes[3];
							break;

						// FUNDS : health
						case 1:
							calccity->stat[i] += floor((building.stat[i] * calccity->funds[3]) / 100);
							break;

						// FUNDS : crime
						case 6:
							calccity->stat[i] += floor((building.stat[i] * calccity->funds[0]) / 100);
							break;

						// FUNDS : firehazard
						case 7:
							calccity->stat[i] += floor((building.stat[i] * calccity->funds[1]) / 100);
							break;

						// FUNDS : education
						case 2:
							calccity->stat[i] += floor((building.stat[i] * calccity->funds[2]) / 100);
							break;

						// special calculation of the annual cost
						case 15:
							for (int j = 0; j < 4; j ++)
							{
								if (building.funds[j])
									calccity->stat[i] += building.funds[j] * calccity->funds[j];
							}
							calccity->stat[i] += building.stat[i];
							break;

						default:
							calccity->stat[i] += building.stat[i];
							break;
					}
				}
			}
		}
	}

	calccity->stat[17] -= calccity->stat[16];
	if (calccity->stat[17] < 0) calccity->stat[17] = 0;

	calccity->stat[19] -= calccity->stat[18];
	if (calccity->stat[19] < 0) calccity->stat[19] = 0;

	// Others stats
	calccity->stat[0] -= floor(calccity->misc[1] / 2);
	calccity->stat[1] -= floor(calccity->misc[1] / 10);
	calccity->stat[2] -= floor(0.3 * (calccity->misc[1] + calccity->stat[14]) - 0.7 * calccity->stat[13]);
	calccity->stat[3] -= floor(calccity->misc[1] / 10);
	calccity->stat[4] -= floor(calccity->misc[1] / 2);
	calccity->stat[5] -= floor(calccity->misc[1] / 2);

	calccity->stat[6] += floor(calccity->misc[1] / 10);
	calccity->stat[7] += floor(calccity->misc[1] / 2);
	calccity->stat[9] += floor(calccity->misc[1] / 2);

	calccity->stat[20] += floor(calccity->misc[1] / 1000);
	calccity->stat[21] -= floor(calccity->misc[1] / 1000);

	// Happyness
	if (calccity->misc[1])
		calccity->stat[22] = floor((calccity->misc[1] + calccity->stat[22] + calccity->stat[0] + calccity->stat[1] + calccity->stat[2] + calccity->stat[3] - calccity->stat[6] - calccity->stat[7] - calccity->stat[9] - 10 * calccity->taxes[0]) / calccity->misc[1]);


	calccity->misc[3] = 0;
	calccity->misc[4] = 0;

	// Population out
	if (calccity->stat[17] < 0 || calccity->stat[19] < 0 || calccity->stat[3] < 0) calccity->misc[4] += 20;
	if ((calccity->stat[20] > 0 || calccity->stat[1] < 0) && calccity->misc[1] > 30000) calccity->misc[4] += 13;
	
	for (int i = 0; i < 6; i ++)
		if (calccity->stat[i] <= 0) calccity->misc[4] += 25;

	if (calccity->stat[5] <= -1000) calccity->misc[4] += 30;
	if (calccity->stat[6] > 1000) calccity->misc[4] += 30;
	if (calccity->stat[7] > 1000) calccity->misc[4] += 30;
	if (calccity->stat[9] > 1000) calccity->misc[4] += 4;
	if (calccity->stat[22] < 0) calccity->misc[4] += 4;

	if (calccity->misc[1] > 100 && calccity->taxes[0] > 10) calccity->misc[4] += 5;
	if (calccity->misc[1] > 100 && calccity->taxes[0] > 30) calccity->misc[4] += 10;
	if (calccity->misc[1] > 500 && calccity->taxes[0] > 50) calccity->misc[4] += 50;
	if (calccity->misc[1] > 1000 && calccity->taxes[0] > 70) calccity->misc[4] += 100;
	
	// Population in
	if (calccity->stat[17] > 0 && calccity->stat[19] > 0)
	{
		for (int i = 0; i < 6; i ++)
			if (calccity->stat[i] > 0) calccity->misc[3] += 25;
		
		if (calccity->stat[6] < 0) calccity->misc[3] += 20;
		if (calccity->stat[7] < 0) calccity->misc[3] += 20;
		if (calccity->stat[9] < 0) calccity->misc[3] += 20;

		if (calccity->stat[12] > 0) calccity->misc[3] += 20;
		if (calccity->taxes[0] <= 10) calccity->misc[3] += 5;
	}

	calccity->misc[1] = calccity->misc[1] + calccity->misc[3] - calccity->misc[4];
	if (calccity->misc[1] < 0) calccity->misc[1] = 0;
}



void end_year(struct calccity *calccity)
{
	dclear(C_WHITE);

	drect(0, 0, 127, 6, C_BLACK);
	dprint_opt(33, 1, C_WHITE, C_NONE, 0, 0, "BILAN %d", calccity->year);

	dhline(0, C_BLACK);
	dhline(63, C_BLACK);
	dvline(0, C_BLACK);
	dvline(127, C_BLACK);

	int taxe_housing = calccity->taxes[0] * calccity->misc[1] / 100;
	int taxe_trade = calccity->taxes[1] * calccity->stat[10] / 100;
	int taxe_industry = calccity->taxes[2] * calccity->stat[11] / 100;
	int taxe_export = calccity->taxes[3] * calccity->stat[14] / 100;

	int entry = taxe_housing + taxe_trade + taxe_industry + taxe_export;

	dprint_opt(4, 8, C_BLACK, C_WHITE, 0, 0, "TAXE HABITATION %d", taxe_housing);
	dprint_opt(4, 15, C_BLACK, C_WHITE, 0, 0, "TAXE COMMERCE %d", taxe_trade);
	dprint_opt(4, 22, C_BLACK, C_WHITE, 0, 0, "TAXE INDUSTRIE %d", taxe_industry);
	dprint_opt(4, 29, C_BLACK, C_WHITE, 0, 0, "TAXE EXPORT %d", taxe_export);
	dprint_opt(4, 36, C_BLACK, C_WHITE, 0, 0, "TOTAL %d", entry);
	dprint_opt(4, 43, C_BLACK, C_WHITE, 0, 0, "COUT ANNUEL %d", calccity->stat[15]);
	dprint_opt(4, 50, C_BLACK, C_WHITE, 0, 0, "BILAN %d", entry - calccity->stat[15]);

	calccity->misc[0] = calccity->misc[0] + entry - calccity->stat[15];
	if (calccity->misc[0] < 0) calccity->misc[0] = 0;

	dupdate();

	int key = 0;
	int opt = GETKEY_DEFAULT & ~GETKEY_MOD_SHIFT & ~GETKEY_MOD_ALPHA & ~GETKEY_REP_ARROWS;
	int timeout = 0;

	while (key != KEY_ALPHA)
		key = getkey_opt(opt, &timeout).key;
}


void check(struct map *map, const int x, const int y)
{
	switch (map->id[y][x])
	{	
		// shorelines
		case 0:
			int shore_id = 110;
			if ((y - 1 >= 0) && map->id[y - 1][x] != 1) shore_id += 8;
			if ((y + 1 < 50) && map->id[y + 1][x] != 1) shore_id += 1;
			if ((x - 1 >= 0) && map->id[y][x - 1] != 1) shore_id += 4;
			if ((x + 1 < 50) && map->id[y][x + 1] != 1) shore_id += 2;

			if (map->data[y][x] != 125 && map->data[y][x] != 126 && shore_id == 125) shore_id += rand() % 2;			
			map->data[y][x] = shore_id;
			break;

		// roads
		case 15:
			int road_id = 80;
			if ((y - 1 >= 0) && map->id[y - 1][x] == 15) road_id += 8;
			if ((y + 1 < 50) && map->id[y + 1][x] == 15) road_id += 1;
			if ((x - 1 >= 0) && map->id[y][x - 1] == 15) road_id += 4;
			if ((x + 1 < 50) && map->id[y][x + 1] == 15) road_id += 2;
			
			if (road_id > 80) road_id --;
			map->data[y][x] = road_id;
			break;

		// railways
		case 18:
			int rail_id = 95;
			if ((y - 1 >= 0) && map->id[y - 1][x] == 18) rail_id += 8;
			if ((y + 1 < 50) && map->id[y + 1][x] == 18) rail_id += 1;
			if ((x - 1 >= 0) && map->id[y][x - 1] == 18) rail_id += 4;
			if ((x + 1 < 50) && map->id[y][x + 1] == 18) rail_id += 2;
			
			if (rail_id > 95) rail_id --;
			map->data[y][x] = rail_id;
			break;
	}
}


int check_harbor(struct map *map, const int x, const int y)
{
	if (map->id[y][x - 1] == 1) return 0;
	if (map->id[y][x + 1] == 1) return 1;
	if (map->id[y - 1][x] == 1) return 2;
	if (map->id[y + 1][x] == 1) return 3;

	return 4;
}


int get_reference_id(const unsigned char tile_id)
{
	switch (tile_id)
	{
		case 0: case 1:
			return 17;
			break;

		case 50: case 51: case 60: case 61:
			return 21;
			break;

		case 3: case 4: case 13: case 14:
			return 22;
			break;

		case 42: case 43: case 52: case 53:
			return 26;
			break;
		
		case 28: case 29: case 38: case 39:
			return 33;
			break;
		
		case 10: case 11: case 20: case 21:
			return 34;
			break;
		
		case 5: case 6: case 15: case 16:
			return 35;
			break;
		
		case 7: case 8: case 17: case 18:
			return 36;
			break;
		
		case 30: case 31: case 40: case 41:
			return 37;
			break;
		
		case 26: case 27: case 36: case 37:
			return 38;
			break;
		
		case 22: case 23: case 32: case 33:
			return 39;
			break;
		
		case 24: case 25: case 34: case 35:
			return 40;
			break;
		
		case 2: case 12:
			return 41;
			break;		
	}
	return 0;
}


void destruction(struct map *map, int loc_x, int loc_y)
{
	extern const struct building buildings[42];
	
	unsigned char ref_id;
	if (map->id[loc_y][loc_x] == -1) ref_id = get_reference_id(map->data[loc_y][loc_x]);
	else ref_id = map->id[loc_y][loc_x];
	
	const struct building building = buildings[ref_id];
	const int ref_x = loc_x, ref_y = loc_y;

	if (map->id[ref_y - 1][ref_x] == ref_id) loc_y --;
	if (map->id[ref_y - 1][ref_x - 1] == ref_id){loc_x --; loc_y --;}
	if (map->id[ref_y][ref_x - 1] == ref_id) loc_x --;

	for (int y = loc_y; y < loc_y + building.size[1]; y ++)
	{
		for (int x = loc_x; x < loc_x + building.size[0]; x ++)
		{
			map->data[y][x] = 125 + rand() % 2;
			map->id[y][x] = 0;
		}
	}
}


void disaster(struct calccity *calccity, struct map *map, const int destruction_rate)
{
	for (int y = 0; y < 50; y ++)
	{
		for (int x = 0; x < 50; x ++)
		{
			if (map->id[y][x] > 1 && rand() % destruction_rate <= destruction_rate / 10)
			{
				map->id[y][x] = 0;
				map->data[y][x] = 125 + rand() % 2; 

				// Large building check
				if (map->id[y][x + 1] == -1)
				{
					map->id[y][x + 1] = 0;
					map->data[y][x + 1] = 125 + rand() % 2;
				}
				if (map->id[y + 1][x + 1] == -1)
				{
					map->id[y + 1][x + 1] = 0;
					map->data[y + 1][x + 1] = 125 + rand() % 2;
				}
				if (map->id[y + 1][x] == -1)
				{
					map->id[y][x + 1] = 0;
					map->data[y][x + 1] = 125 + rand() % 2;
				}
				calccity->misc[1] = calccity->misc[1] / (rand() % destruction_rate);
			}
		}
	}
}