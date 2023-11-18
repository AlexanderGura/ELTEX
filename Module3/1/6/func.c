#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "func.h"

void get_dirname(char *dn)
{
	printf("Enter the directory name: ");
	fgets(dn, 20, stdin);
	sscanf(dn, "%s", dn);
}

void check_dir(const char *dirname, int lvl)
{
	DIR *dir = opendir(dirname);
	if (dir == NULL)
	{
		fprintf(stderr, "Couldn't open %s directory!\n", dirname);
		return;
	}

	struct dirent 	*file;
	while ((file = readdir(dir)) != NULL)
		check_type(file, lvl);

	if (closedir(dir) == -1)
	{
		fprintf(stderr, "Couldn't close %s directory!\n", dirname);
		return;
	}
}

void check_type(struct dirent *file, int lvl)
{
	if (strncmp(file->d_name, ".", 1) == 0)
		return;

	for (int i = 0; i < lvl; i++)
		printf("\t");

	switch(file->d_type)
	{
		case DT_LNK:
		 printf("%s - symlink\n", file->d_name);
		 break;

		case DT_REG:
		 printf("%-20s - regular file\n", file->d_name);
		 break;

		case DT_DIR:
		 printf("%s - directory\n", file->d_name);
		 check_dir(file->d_name, lvl + 1);
		 break;

		case DT_CHR:
		 printf("%s - character device\n", file->d_name);
		 break;

		case DT_BLK:
		 printf("%s - block divece\n", file->d_name);
		 break;

		case DT_FIFO:
		 printf("%s - FIFO\n", file->d_name);
		 break;

		case DT_SOCK:
		 printf("%s - socket\n", file->d_name);
		 break;

		default:
		 printf("%s - unknown\n", file->d_name);
		 break;
		}

}
