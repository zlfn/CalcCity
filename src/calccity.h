#ifndef _CALCCITY_H
#define _CALCCITY_H

#include <stdlib.h>

struct calccity
{

	// main statistics
	/* 
	housing,
	health,
	education,
	food,
	work,
	transport,

	crime,
	firehazard,
	nuclearhazard,
	pollution,

	commercial,
	industrial,
	production,
	import,
	export,
	annual_cost,
	
	water_consumption,
	power_consumption,
	power_supply,
	grabage
	graves,
	*/
	unsigned long stat[21];

	// some others statistics = {treasure, population, safety, hapyness, birth_rate, death_rate, immigration, emigration, water_supply}
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
	int cursor_size[2];
};


struct map
{
	unsigned char data[50][50];
};


struct building
{
	char *name;
	
	unsigned char *id;
	int cost;
	unsigned char size[2];

	/* 
	housing,
	health,
	education,
	food,
	work,
	transport,

	crime,
	firehazard,
	nuclearhazard,
	pollution,

	commercial,
	industrial,
	production,
	import,
	export,
	annual_cost,
	
	water_consumption,
	power_consumption,
	power_supply,
	grabage
	graves,
	*/
	unsigned int stat[21];

	// commercial, industrial, export
	unsigned int taxes[3];

	// police, firemen, education, heathcare
	unsigned int funds[4];

};


#define ENGINE_TICK 100

static const struct building buildings[41];

#endif /* _CALCCITY_H */