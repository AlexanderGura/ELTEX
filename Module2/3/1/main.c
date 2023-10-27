#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define LEN_BITS  10
#define LEN_DIGITS 3

void alph_mode(char*);
void digit_mode();

int main()
{
	struct stat stat_file;
	stat("main.c", &stat_file);
	printf("%d", stat_file.st_mode);

	char mode[LEN_BITS];
	strncpy(mode, "000000000", LEN_BITS);

	alph_mode(mode);

	return 0;
}

void alph_mode(char* mode)
{
	printf("Enter permission in alphabetic format: ");
	char permission[LEN_BITS];
	fgets(permission, LEN_BITS, stdin);

	for (int i = 0; i < LEN_BITS - 1; i++)
		if (permission[i] != '-')
			mode[i] = '1';

	printf("%s\n", mode);
}

void digit_mode()
{
	printf("Enter permission in digits format: ");
	int permission;
	scanf("%d", &permission);
	getchar();

}
