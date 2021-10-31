#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "calccity.h"

// title_screen : display title screen
void title_screen(void);

// display_map : display the current state of the map
void display_map(struct calccity *calccity, struct camera *camera, struct map *map);

#endif /* _DISPLAY_H */