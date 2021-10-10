#ifndef _CALCCITY_H
#define _CALCCITY_H

struct calccity = 
{
	// human's statistics = {happyness, health, education, housing, work, food} 
	signed long humans[6] = {0};

	// population evolution = {population, birth_rate, death_rate, immigration, emigration}
	signed long population[5] = {0};

	// trade statistics = {import, export, production, commercial, industrial, annual_cost}
	signed long trade[6] = {0};

	// production = {water, power}
	signed long production[2] = {0};

	// consumption = {water, power}
	signed long consumption[2] = {0};

	// some others statistics = {crime, safety, fire_hazard, nuclear_hazard, pollution, transport, grabage, graves}
	signed long misc[8] = {0};

	// taxes in percents on {housing, trade, industry, export}
	int taxes[4] = {10, 10, 10, 10};

	// fund in percents on {police, fireman, education, heathcare}
	int funds[4] = {0};

	// in-game time
	int month = 1, year = 1900;
	int blinker = 0;

	// in-game options
	bool disaster = true;
	bool show_fps = false;
	int time_speed = 30;

};


struct camera = 
{
	int x, y;
	int zoom;

	int cursor_x, cursor_y;
};


struct map = 
{
	unsigned char map_data[50][50];
};


#endif /* _CALCCITY_H */