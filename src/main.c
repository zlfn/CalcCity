#include "core.h"


int main(void)
{
	title_screen();

	// Game initialisation
	struct calccity calccity;
	struct camera camera;
	struct map map;
	default_values(&calccity, &camera, &map);

	main_loop(&calccity, &camera, &map);
	return 1;
}