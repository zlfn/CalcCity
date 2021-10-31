#ifndef _CORE_H
#define _CORE_H

#include "calccity.h"
#include "display.h"

// callback_tick : time function
int callback_tick(volatile int *tick);

// default_values : initialize the game
void default_values(struct calccity *current_game, struct camera *camera, struct map *map);

// rtc_key : get a key with RTC system
int rtc_key(void);

// main_loop : game main loop
void main_loop(struct calccity *calccity, struct camera *camera, struct map *map);

#endif /* _CORE_H */