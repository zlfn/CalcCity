#ifndef _CALCCITY_H
#define _CALCCITY_H

struct calccity = 
{
	// human's statistics = {happyness, health, education, housing, work, food, transport, grabage, graves} 
	signed long statistics[9] = {0};

	// population evolution = {birth, death, immigration, emmigration}

	// production = {water, power}
	signed long production[2] = {0};

	// consumption = {water, power}
	signed long consumption[2] = {0};

	// risks and safety = {crime, safety, fire_hazard, nuclear_hazard, pollution}
	signed long risks[5] = {0};

	// taxes on {housing, trade, industry, export}
	int taxes[4] = {10, 10, 10, 10};

	// industry statistics = {import, export, production, commercial, industrial, }
};

struct mouse = 
{

};

#endif /* _CALCCITY_H */