#include <gint/display.h>
#include "core.h"


int main(void)
{
	extern font_t font_calccity;
	dfont(&font_calccity); 

	title_screen();

	// Game initialisation
	struct calccity calccity;
	struct camera camera;
	struct map map;
	default_values(&calccity, &camera, &map);

	main_loop(&calccity, &camera, &map);
	return 1;
}