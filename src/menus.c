#include <gint/keyboard.h>
#include <gint/display.h>
#include <gint/std/stdlib.h>

#include "menus.h"


void menu_5(struct calccity *calccity)
{
	int scroll = 0, key = 0;
	int opt = GETKEY_DEFAULT & GETKEY_REP_ARROWS;
	int timeout = 0;

	static const char *names[23] = {
			"GENERAL",
		"ARGENT",
		"POPULATION",
		"BONHEUR",
		"SANTE",
		"EDUCATION",
		"LOGEMENT",
		"TRAVAIL",
		"NOURRITURE",
		"EAU",
		"ENERGIE",
		"TRANSPORT",
		"DECHETS",
		"TOMBES",
			"RISQUES",
		"CRIME",
		"RISQUE INCENDIE",
		"RISQUE NUCLEAIRE",
		"POLLUTION",
			"COMMERCE",
		"PRODUCTION",
		"IMPORT",
		"EXPORT"
	};

	long int values[23] = {
			-1,
		calccity->misc[0],
		calccity->population[0],
		calccity->humans[0],
		calccity->humans[1],
		calccity->humans[2],
		calccity->humans[3],
		calccity->humans[4],
		calccity->humans[5],
		calccity->production[0],
		calccity->production[1],
		calccity->misc[6],
		calccity->misc[7],
		calccity->misc[8],
			-1,
		calccity->misc[1],
		calccity->misc[3],
		calccity->misc[4],
		calccity->misc[5],
			-1,
		calccity->trade[2],
		calccity->trade[0],
		calccity->trade[1]
	};

	while (key != KEY_ALPHA)
	{
		dclear(C_WHITE);
		
		// Title
		drect(0, 0, 127, 6, C_BLACK);
		dtext(27, 1, C_WHITE, "STATISTIQUES");

		// Frame
		dhline(0, C_BLACK);
		dhline(63, C_BLACK);
		dvline(0, C_BLACK);
		dvline(127, C_BLACK);

		// Scroll bar
		dline(5, 6, 5, 63, C_BLACK);
		drect(2, scroll + 8, 3, 8 + scroll + 38, C_BLACK);

		for (int i = 0; i < 8; i ++)
		{
			if (values[i + scroll] < 0)
			{
				drect(5, 7 + i * 7, 127, 13 + i * 7, C_BLACK);
				dtext(12, 8 + i * 7, C_WHITE, names[i + scroll]);
			}
			else
				dprint(7, 8 + i * 7, C_BLACK, "%s %lu", names[i + scroll], values[i + scroll]);
		}

		dupdate();
		
		key = getkey_opt(opt, &timeout).key;

		switch (key)
		{
			case KEY_UP:
				if (scroll > 0) scroll --;
				break;

			case KEY_DOWN:
				if (scroll < 15) scroll ++;
				break;
		}

	}
}


void menu_4(struct calccity *calccity)
{
	int choice = 0, key = 0;
	int opt = GETKEY_DEFAULT & ~GETKEY_MOD_SHIFT & ~GETKEY_MOD_ALPHA & GETKEY_REP_ARROWS;
	int timeout = 0;

	while (key != KEY_ALPHA)
	{
		dclear(C_WHITE);
		drect(0, 0, 127, 6, C_BLACK);
		dtext(24, 1, C_WHITE, "TAXES & FONDS");

		dhline(0, C_BLACK);
		dhline(63, C_BLACK);
		dvline(0, C_BLACK);
		dvline(127, C_BLACK);

		dtext(7, 8, C_BLACK, "TAXE HABITATION");
		dtext(7, 15, C_BLACK, "TAXE COMMERCE");
		dtext(7, 22, C_BLACK, "TAXE INDUSTRIE");
		dtext(7, 29, C_BLACK, "TAXE EXPORT");
		dtext(7, 36, C_BLACK, "FOND POLICE");
		dtext(7, 43, C_BLACK, "FOND POMPIER");
		dtext(7, 50, C_BLACK, "FOND ECOLE");
		dtext(7, 57, C_BLACK, "FOND S.SOCIALE");

		for (int i = 0; i < 4; i ++)
		{
			dprint(97, 8 + i * 7, C_BLACK, "%d%%", calccity->taxes[i]);
			dprint(97, 36 + i * 7, C_BLACK, "%d%%", calccity->funds[i]);
		}


		dtext(2, 8 + choice * 7, C_BLACK, ">");
		dtext(121, 8 + choice * 7, C_BLACK, "<");
		dupdate();
		
		key = getkey_opt(opt, &timeout).key;
		switch (key)
		{
			case KEY_UP:
				if (choice > 0) choice --;
				break;

			case KEY_DOWN:
				if (choice < 7) choice ++;
				break;

			case KEY_LEFT:
				if (choice < 5 && calccity->taxes[choice] > 0) calccity->taxes[choice] --;
				if (choice >= 5 && calccity->funds[choice - 5] > 0) calccity->funds[choice - 5] --;
				break;

			case KEY_RIGHT:
				if (choice < 5 && calccity->taxes[choice] < 100) calccity->taxes[choice] ++;
				if (choice >= 5 && calccity->funds[choice - 5] < 100) calccity->funds[choice - 5] ++;
				break;
		}

	}
}


int menu_6(struct calccity *calccity)
{
	int choice = 0, key = 0;
	int opt = GETKEY_DEFAULT & ~GETKEY_MOD_SHIFT & ~GETKEY_MOD_ALPHA & GETKEY_REP_ARROWS;
	int timeout = 0;

	while (key != KEY_ALPHA)
	{
		int prcnt = 100 - (calccity->time_speed * 100 / 10000);

		dclear(C_WHITE);

		drect(0, 0, 127, 6, C_BLACK);
		dtext(39, 1, C_WHITE, "OPTIONS");
		
		dhline(0, C_BLACK);
		dhline(63, C_BLACK);
		dvline(0, C_BLACK);
		dvline(127, C_BLACK);

		dtext(7, 9, C_BLACK, "ANIMATIONS ");
		dtext(7, 16, C_BLACK, "CATASTROPHES");
		dtext(7, 23, C_BLACK, "VITESSE DU JEU");
		dtext(7, 30, C_BLACK, "QUITTER LE JEU");
		dtext(7, 37, C_BLACK, "REPRENDRE");

		if (calccity->animation)
			dtext(85, 9, C_BLACK, "on");
		else
			dtext(85, 9, C_BLACK, "off");

		if (calccity->disaster)
			dtext(85, 16, C_BLACK, "on");
		else
			dtext(85, 16, C_BLACK, "off");

		dprint(97, 23, C_BLACK, "%d%%", prcnt + 1);


		dtext(2, 9 + choice * 7, C_BLACK, ">");
		dtext(121, 9 + choice * 7, C_BLACK, "<");
		dupdate();
		
		key = getkey_opt(opt, &timeout).key;

		switch (key)
		{
			case KEY_UP:
				if (choice > 0) choice --;
				break;

			case KEY_DOWN:
				if (choice < 4) choice ++;
				break;

			case KEY_SHIFT:
				switch (choice)
				{
					case 0:
						calccity->animation = (calccity->animation + 1) % 2;
						break;

					case 1:
						calccity->disaster = (calccity->disaster + 1) % 2;
						break;

					case 3:
						return 1;
						break;

					case 4:
						return 0;

				}
				break;

			case KEY_LEFT:
				if (choice == 2 && calccity->time_speed < 10000) calccity->time_speed += 100;
				break;

			case KEY_RIGHT:
				if (choice == 2 && calccity->time_speed > 100) calccity->time_speed -= 100;
				break;
		}
	}
	return 0;
}
