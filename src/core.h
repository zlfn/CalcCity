#ifndef _CORE_H
#define _CORE_H

#include <stdbool.h>
#include "calccity.h"
#include "display.h"
#include "menus.h"

// callback_tick : time function
int callback_tick(volatile int *tick);

// default_values : initialize the game
void default_values(struct calccity *current_game, struct camera *camera, struct map *map);

// rtc_key : get a key with RTC system
int rtc_key(void);

// next_step : compute in-game time
void next_step(struct calccity *calccity, struct map *map);

// main_loop : game main loop, manage key, menu, map actualization and building
void main_loop(struct calccity *calccity, struct camera *camera, struct map *map);

// keyboard_managment : get the key, manage input and open menus
void keyboard_managment(struct camera *camera, const int key, const int build_mode);

// can_build : test if the build is legit
bool can_build(struct calccity *calccity, struct map *map, struct building *building, const unsigned short x, const unsigned short y, unsigned char *index);

// exit_build_mode : reset build mode and cusor
void exit_build_mode(struct camera *camera, int *build_mode);

// large_building : detect large buildings and adjust the building's id
struct building large_building(struct map *map, int *build_mode, short unsigned int *loc_x, short unsigned int *loc_y);

// update_stat : compute the new stat with buildings
void update_stat(struct calccity *calccity, struct map *map);

// end_year : display the year's balance sheet
void end_year(struct calccity *calccity);

// check_shorelines : check the shorelines, roads and railways
void check(struct map *map, const int x, const int y);

// check_harbor : check the harbor's orientation
int check_harbor(struct map *map, const int x, const int y);

// get_reference_id : get the id of large buildings
int get_reference_id(const unsigned char tile_id);

// destruction : manage deconstruction
void destruction(struct map *map, int loc_x, int loc_y);

// disaster : manage disasters
void disaster(struct calccity *calccity, struct map *map, const int destruction_rate);

#endif /* _CORE_H */