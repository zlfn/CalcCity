#include <gint/keyboard.h>
#include <gint/display.h>
#include <stdlib.h>

#include "menus.h"


struct building menu_12(struct calccity *calccity, struct camera *camera, struct map *map, int *build_mode, int menu)
{
	extern const bopti_image_t img_fn_1;
	extern const bopti_image_t img_fn_2;
	extern const struct building buildings[42];

	int key = 0, end = 0, x = 0, y = 0;

	while (!end)
	{
		dclear(C_WHITE);
		display_main(calccity, camera, map, 0);
		
		if (menu == 1)
		{
			drect(3, 57, 19, 64, C_INVERT);
			dimage(3, 11, &img_fn_1);
			drect(9 * x + 4, 9 * y + 12, 9 * x + 11, 9 * y + 19, C_INVERT);
		}
		else
		{
			drect(21, 57, 39, 64, C_INVERT);
			dimage(20, 11, &img_fn_2);
			drect(9 * x + 21, 9 * y + 12, 9 * x + 28, 9 * y + 19, C_INVERT);

		}
		dupdate();

		key = rtc_key();
		switch (key)
		{
			case KEY_UP:
				if (y > 0) y --;
				break;

			case KEY_LEFT:
				if (x > 0) x --;
				break;

			case KEY_DOWN:
				if (y < 4) y ++;
				break;

			case KEY_RIGHT:
				if (x < (1 + menu)) x ++;
				break;

			case KEY_ALPHA:
				end = 2;
				break;

			case KEY_SHIFT:
				end = 1;
				break;

			case KEY_F1:
				menu = 1;
				x = 0;
				y = 0;
				break;

			case KEY_F2:
				menu = 2;
				x = 0;
				y = 0;
				break;

			case KEY_F4:
				menu_4(calccity);
				end = 2;
				break;

			case KEY_F5:
				menu_5(calccity);
				end = 2;
				break;

			case KEY_F6:
				menu_6(calccity);
				end = 2;
				break;
		}
	}

	if (end == 1)
	{
		if (menu == 1)
		{
			*build_mode = x + y * 3;
			return buildings[x + y * 3];
		}
		else
		{
			*build_mode = 15 + x + y * 4;
			return buildings[15 + x + y * 4];
		}
	}

	else
	{
		*build_mode = -1;
		struct building default_building = {0};
		return default_building;
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
				if (choice < 4 && calccity->taxes[choice] > 0) calccity->taxes[choice] --;
				if (choice >= 4 && calccity->funds[choice - 4] > 0) calccity->funds[choice - 4] --;
				break;

			case KEY_RIGHT:
				if (choice < 4 && calccity->taxes[choice] < 100) calccity->taxes[choice] ++;
				if (choice >= 4 && calccity->funds[choice - 4] < 100) calccity->funds[choice - 4] ++;
				break;
		}

	}
}


void menu_5(struct calccity *calccity)
{
	int scroll = 0, key = 0;
	int opt = GETKEY_DEFAULT & GETKEY_REP_ARROWS;
	int timeout = 0;

	static const char *names[27] = {
			"GENERAL",
		"ARGENT",
		"POPULATION",
		"BONHEUR",
		"LOGEMENT",
		"SANTE",
		"EDUCATION",
		"NOURRITURE",
		"TRAVAIL",
		"TRANSPORT",
			"SECURITE",
		"CRIME",
		"INCENDIE",
		"NUCLEAIRE",
		"POLLUTION",
			"ECONOMIE",
		"COMMERCE",
		"INDUSTRIE",
		"PRODUCTION",
		"IMPORT",
		"EXPORT",
		"COUT ANNUEL",
			"DIVERS",
		"EAU",
		"ENERGIE",
		"DECHETS",
		"TOMBES",
	};

	long values[27] = {0};
	int offset = 0;

	for (int i = 0; i < 27; i ++)
	{
		switch (i)
		{
			case 0: case 10: case 15: case 22:
				values[i] = 0;
				offset ++;
				break;

			case 1: case 2:
				values[i] = calccity->misc[i - 1];
				offset ++;
				break;

			case 3:
				values[i] = calccity->stat[22];
				offset ++;
				break;

			case 23:
				values[i] = calccity->stat[17] - calccity->stat[16];
				offset --;
				break;

			case 24:
				values[i] = calccity->stat[19] - calccity->stat[18];
				offset --;
				break;

			default:
				values[i] = calccity->stat[i - offset];
				break;
		}
	}

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
		drect(2, scroll + 8, 3, 8 + scroll + 34, C_BLACK);

		for (int i = 0; i < 8; i ++)
		{
			if (i + scroll == 0 || i + scroll == 10 || i + scroll == 15 || i + scroll == 22)
			{
				drect(5, 7 * i + 7, 127, 7 * i + 13, C_BLACK);
				dtext(20, 7 * i + 8, C_WHITE, names[i + scroll]);
			}
			else
			{
				dprint(7, 7 * i + 8, C_BLACK, "%s", names[i + scroll]);
				dprint(60, 7 * i + 8, C_BLACK, "%d", values[i + scroll]);
			}
		}

		dupdate();
		
		key = getkey_opt(opt, &timeout).key;

		switch (key)
		{
			case KEY_UP:
				if (scroll > 0) scroll --;
				break;

			case KEY_DOWN:
				if (scroll < 19) scroll ++;
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
		int prcnt = 100 - (calccity->time_speed * 100 / 7500);

		dclear(C_WHITE);

		drect(0, 0, 127, 6, C_BLACK);
		dtext(42, 1, C_WHITE, "OPTIONS");
		
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

		dprint(85, 23, C_BLACK, "%d%%", prcnt + 1);


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
