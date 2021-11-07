#ifndef _CALCCITY_H
#define _CALCCITY_H

#include <stdlib.h>

struct calccity
{

	// main statistics
	/* 
	0 housing,
	1 health,
	2 education,
	3 food,
	4 work,
	5 transport,

	6 crime,
	7 firehazard,
	8 nuclearhazard,
	9 pollution,

	10 commercial,
	11 industrial,
	12 production,
	13 import,
	14 export,
	15 annual_cost,
	
	16 water_consumption,
	17 water_supply,
	18 power_consumption,
	19 power_supply,
	20 grabage,
	21 graves,
	22 happyness
	*/
	int stat[23];

	// some others statistics = {treasure, population, safety, population in, population out}
	int misc[5];
	
	// taxes in percents on {housing, trade, industry, export}
	int taxes[4];

	// fund in percents on {police, fireman, education, heathcare}
	int funds[4];

	// in-game time
	int month, year;
	int blinker_water;
	int blinker_alert;
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

	unsigned char id[50][50];
};


struct building
{	
	char *id;
	int cost;
	unsigned char size[2];

	int stat[23];

	// commercial, industrial, export
	int taxes[3];

	// police, firemen, education, heathcare
	int funds[4];

	char *name;
};


#define ENGINE_TICK 100

#endif /* _CALCCITY_H */