#include <stdio.h>
#include <gint/bfile.h>
#include <gint/hardware.h>
#include "save.h"

char const *filename_u8 = "/CalcCity.sav";
uint16_t const *filename_u16 = u"\\\\fls0\\CalcCity.sav";


void read_save(struct calccity *calccity, struct camera *camera, struct map *map)
{
	if (gint[HWCALC] == HWCALC_G35PE2)
	{
		FILE *fp;
		fp = fopen(filename_u8, "rb");

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
	else
	{
		int fd = BFile_Open(filename_u16, BFile_ReadOnly);
		if (fd < 0)
			default_values(calccity, camera, map);
		else
		{
			BFile_Read(fd, calccity, sizeof *calccity, -1);
			BFile_Read(fd, camera, sizeof *camera, -1);
			BFile_Read(fd, map, sizeof *map, -1);
			BFile_Close(fd);
		}
	}
}


void write_save(const struct calccity *calccity, const struct camera *camera, const struct map *map)
{
	if (gint[HWCALC] == HWCALC_G35PE2)
	{
		FILE *fp;
		fp = fopen(filename_u8, "wb");

		if (fp != NULL)
		{
			fwrite(calccity, sizeof *calccity, 1, fp);
			fwrite(camera, sizeof *camera, 1, fp);
			fwrite(map, sizeof *map, 1, fp);

			fclose(fp);
		}
	}
	else
	{
		// Only even-size writes
		if((sizeof *calccity) & 1 ||
		   (sizeof *camera) & 1 ||
		   (sizeof *map) & 1)
			return;

		BFile_Remove(filename_u16);
		int size = sizeof *calccity + sizeof *camera + sizeof *map;

		int rc = BFile_Create(filename_u16, BFile_File, &size);
		if(rc < 0) return;

		int fd = BFile_Open(filename_u16, BFile_WriteOnly);
		if(fd < 0) return;

		BFile_Write(fd, calccity, sizeof *calccity);
		BFile_Write(fd, camera, sizeof *camera);
		BFile_Write(fd, map, sizeof *map);
		BFile_Close(fd);
	}
}
