#include <stdio.h>

#include "save.h"


const char *filename = "/CalcCity.sav";


void read_save(struct calccity *calccity, struct camera *camera, struct map *map)
{
	FILE *fp;
	fp = fopen(filename, "rb");

	// If the backup doesn't exist
	if (fp == NULL)
		default_values(calccity, camera, map);
	else
	{
		fread(calccity, 1, sizeof *calccity, fp);
		fread(camera, 1, sizeof *camera, fp);
		fread(map, 1, sizeof *map, fp);
	
		fclose(fp);
	}
}


void write_save(const struct calccity *calccity, const struct camera *camera, const struct map *map)
{
	FILE *fp;
	fp = fopen(filename, "wb");
	
	if (fp != NULL)
	{
		fwrite(calccity, sizeof *calccity, 1, fp);
		fwrite(camera, sizeof *camera, 1, fp);
		fwrite(map, sizeof *map, 1, fp);

		fclose(fp);
	}
}
