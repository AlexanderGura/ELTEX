#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "func.h"

int menu()
{
	printf("\n1. Alph format;\n");
	printf("2. Digit format;\n");
	printf("3. Check file permission;\n");
	printf("4. Change file permission;\n");
	printf("Enter your choice ('q' - to quit): ");

	char choice = getchar();
	getchar();
	switch(choice)
	{
		case '1':
			printf("\nEnter permission in alphabetic format: ");
			char perm_str[LEN_BITS];
			fgets(perm_str, LEN_BITS, stdin);
			getchar();
			alph_mode(perm_str);
			return 1;
		case '2':
			printf("\nEnter permission in digit format: ");
			int perm_int;
			scanf("%d", &perm_int);
			getchar();
			digit_mode(perm_int);
			return 1;
		case '3':
			get_stat();
			return 1;
		case '4':
			return 1;
		default:
			return 0;
	}
}

void alph_mode(char* permission)
{
	int mode = 0;
	for (int i = 0; i < LEN_BITS - 1; i++)
		if (permission[i] != '-')
			mode |= (1 << i);

	print_bin(mode);
}

void digit_mode(int permission)
{
	int mode = 0;
	int index = 0;
	for (int i = 0; i < LEN_DIGITS; i++)
	{
		int x = permission % 10;
		for (int j = 0; j < LEN_DIGITS; j++)
		{
			mode |= ((x % 2) << index);
			x /= 2;
			index++;
		}
		permission /= 10;
	}
	print_bin(mode);

}

void get_stat()
{
	struct stat stat_file;
	//char filename[LEN_FILE];
	//printf("Enter file name: ");
	//fgets(filename, LEN_FILE, stdin);
	//printf("%s", filename);

	stat("main.c", &stat_file);
	int mode = stat_file.st_mode;
	int mask = 0x1ff;
	mode &= mask;
	printf("\nDigits format - %o", mode);
}

void print_bin(int mode)
{
	while (mode > 0)
	{
		printf("%d", mode % 2);
		mode /= 2;
	}
	printf("\n");
}
