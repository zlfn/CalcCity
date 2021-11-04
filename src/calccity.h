#ifndef _CALCCITY_H
#define _CALCCITY_H

#include <gint/std/stdlib.h>

struct calccity
{
	// human's statistics = {happyness, health, education, housing, work, food} 
	unsigned long humans[6];

	// population evolution = {population, birth_rate, death_rate, immigration, emigration}
	unsigned long population[5];

	// trade statistics = {import, export, production, commercial, industrial, annual_cost}
	unsigned long trade[6];

	// production = {water, power}
	unsigned long production[2];

	// consumption = {water, power}
	unsigned long consumption[2];

	// some others statistics = {treasure, crime, safety, fire_hazard, nuclear_hazard, pollution, transport, grabage, graves}
	unsigned long misc[9];

	// taxes in percents on {housing, trade, industry, export}
	unsigned int taxes[4];

	// fund in percents on {police, fireman, education, heathcare}
	unsigned int funds[4];

	// in-game time
	int month, year;
	int blinker;
	int tick;

	// in-game options
	uint8_t disaster;
	uint8_t animation;
	int time_speed;
	int menu;

};


struct camera
{
	int x, y;
	int zoom;

	int cursor_x, cursor_y;
};


struct map
{
	unsigned char data[50][50];
};


#define ENGINE_TICK 100

#endif /* _CALCCITY_H */