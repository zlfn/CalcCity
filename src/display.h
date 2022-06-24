#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "calccity.h"
#include "core.h"

// title_screen : display title screen
void title_screen(void);

// main_display : the general display function
void display_main(struct calccity *calccity, struct camera *camera, struct map *map, const int disp_cursor);

// display_large_map : display the current state of the large map
void display_large_map(struct calccity *calccity, struct camera *camera, struct map *map);

// display_mini_map : display the current state of the mini map
void display_mini_map(struct camera *camera, struct map *map);

// display_around : display the screen frame and cursor
void display_around(struct calccity *calccity, struct camera *camera, struct map *map, const int disp_cursor);

// display_message : display the given message with lines breaks
void display_message(char* message);

#endif /* _DISPLAY_H */