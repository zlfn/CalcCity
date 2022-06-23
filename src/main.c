#include <gint/display.h>
#include <gint/gint.h>
#include "core.h"
#include "save.h"


int main(void)
{
	extern font_t font_calccity;
	dfont(&font_calccity); 

	title_screen();

	// Game initialisation
	struct calccity calccity;
	struct camera camera;
	struct map map;
	gint_world_switch(GINT_CALL(read_save, (void *)&calccity, (void *)&camera, (void *)&map));

	// Game
	main_loop(&calccity, &camera, &map);

	// Backup data
	gint_world_switch(GINT_CALL(write_save, (void *)&calccity, (void *)&camera, (void *)&map));

	return 1;
}