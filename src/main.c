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
	struct calccity *calccity;
	calccity = (struct calccity*) malloc(sizeof *calccity);

	struct camera *camera;
	camera = (struct camera*) malloc(sizeof *camera);

	struct map *map;
	map = (struct map*) malloc(sizeof *map);

	// Loading save
	gint_world_switch(GINT_CALL(read_save, (void *)calccity, (void *)camera, (void *)map));

	// Launch the game
	main_loop(calccity, camera, map);

	// Backup data
	gint_world_switch(GINT_CALL(write_save, (void *)calccity, (void *)camera, (void *)map));

	// Free memory
	free(calccity);
	free(camera);
	free(map);

	return 1;
}