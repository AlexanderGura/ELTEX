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
			print_bin(alph_mode(perm_str));
			return 1;
		case '2':
			printf("\nEnter permission in digit format: ");
			int perm_int;
			scanf("%d", &perm_int);
			getchar();
			print_bin(digit_mode(perm_int));
			return 1;
		case '3':
			get_stat();
			return 1;
		case '4':
			set_stat();
			return 1;
		default:
			return 0;
	}
}

int alph_mode(char* permission)
{
	int mode = 0;
	for (int i = 0; i < LEN_BITS - 1; i++)
		if (permission[i] != '-')
			mode |= (1 << i);

	return mode;
}

int digit_mode(int permission)
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
	return mode;

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

	print_bin(mode);
	print_alph(mode);
	printf("Digits format: %o\n", mode);
}

void set_stat()
{
	printf("chmod ");
	char chmod[LEN_CHMOD];
	fgets(chmod, LEN_CHMOD, stdin);
	getchar();

	get_stat();
}

void print_bin(int mode)
{
	printf("Digit format: ");
	while (mode > 0)
	{
		printf("%d", mode % 2);
		mode /= 2;
	}
	printf("\n");
}

void print_alph(int mode)
{
	char alph[LEN_BITS];
	strncpy(alph, "rwxrwxrwx", LEN_BITS);
	printf("Alphabet format: ");
	for (int i = 0; i < LEN_BITS - 1; i++)
	{
		(mode % 2 == 1) ? printf("%c", alph[i]) : printf("-");
		mode /= 2;
	}
	printf("\n");
}
