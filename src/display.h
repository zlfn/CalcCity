#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "calccity.h"

// title_screen : display title screen
void title_screen(void);

// display_large_map : display the current state of the large map
void display_large_map(struct calccity *calccity, struct camera *camera, struct map *map);

// display_around : display the screen frame and cursor
void display_around(struct calccity *calccity, struct camera *camera);

#endif /* _DISPLAY_H */