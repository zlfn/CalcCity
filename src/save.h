#ifndef _SAVE_H
#define _SAVE_H

#include "core.h"
#include "calccity.h"


// read_save : get the save if exists; else returns default values
void read_save(struct calccity *calccity, struct camera *camera, struct map *map);

// write_save : save the game into savefile
void write_save(const struct calccity *calccity, const struct camera *camera, const struct map *map);

#endif /* _SAVE_H */