#ifndef _MENUS_H
#define _MENUS_H

#include "calccity.h"
#include "core.h"

// menu_1 : building 1
struct building menu_1(struct calccity *calccity, struct camera *camera, struct map *map, int *build_mode);

// menu_4 : tax and funds
void menu_4(struct calccity *calccity);

// menu_5 : informations
void menu_5(struct calccity *calccity);

// menu_6 : options
int menu_6(struct calccity *calccity);

#endif /* _MENUS_H */