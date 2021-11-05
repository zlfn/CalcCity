#ifndef _CORE_H
#define _CORE_H

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
void next_step(struct calccity *calccity);

// main_loop : game main loop
void main_loop(struct calccity *calccity, struct camera *camera, struct map *map);

// keyboard_managment : get the key, manage input and open menus
int keyboard_managment(struct calccity *calccity, struct camera *camera, struct map *map, const int key);

// build : manage the build
void build(struct calccity *calccity, struct camera *camera, struct map *map, struct building *building);

#endif /* _CORE_H */