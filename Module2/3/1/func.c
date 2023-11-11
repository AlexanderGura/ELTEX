#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "func.h"

static void clear_input()
{
	for (char c = getchar(); c != '\n'; c = getchar());
}

static int select_choice(char choice)
{
	switch(choice)
	{
		case '1':
			char permission_str[LEN_BITS];
			return enter_alph_format(permission_str);
		case '2':
			int permission_int;
			return enter_dig_format(&permission_int);
		case '3':
			char filename[LEN_FILE];
			printf("Enter file name: ");
			fgets(filename, LEN_FILE, stdin);
			get_stat(filename);
			return 1;
		case '4':
			set_stat();
			return 1;
		case 'q':
		case 'Q':
			printf("\nGood bye, have a good day!\n");
			return 0;
		default:
			printf("Invalid choice!\n");
			return -1;
	}

}

static int enter_alph_format(char *perm)
{
	printf("\nEnter permission in alphabetic format: ");
	fgets(perm, LEN_BITS, stdin);
	clear_input();
	if (strlen(perm) < 9)
	{
		printf("Wrong format!\n");
		return -1;
	}
	int result = alph_mode_to_bin(perm);
	print_bin(result);

	return 1;
}

static int enter_dig_format(int* perm)
{
	printf("\nEnter permission in digit format: ");
	scanf("%d", perm);
	clear_input();
	if (*perm < 100 || *perm > 1000)
	{
		printf("Wrong format!\n");
		return -1;
	}
	int result = digit_mode_to_bin(*perm);
	print_bin(result);
	return 1;

}

static int oct_to_dec(int num)
{
	if (num < 100 || num > 1000)
		return -1;

	int pow[] = {1, 8, 64};
	int result = 0;
	for(int i = 0; i < sizeof(pow) / sizeof(int); i++)
	{
		result += (num % 10) * pow[i];
		num /= 10;
	}
	return result;
}


int alph_mode_to_bin(char* permission)
{
	int mode = 0;
	for (int i = 0; i < LEN_BITS - 1; i++)
		if (permission[i] != '-')
			mode |= (1 << i);

	return mode;
}

int digit_mode_to_bin(int permission)
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


int menu()
{
	printf("\n1. Alph format;\n");
	printf("2. Digit format;\n");
	printf("3. Check file permission;\n");
	printf("4. Change file permission;\n");
	printf("Enter your choice ('q' - to quit): ");

	char choice = getchar();
	clear_input();
	return select_choice(choice);
}

int get_stat(char *filename)
{
	struct stat stat_file;
	sscanf(filename, "%s", filename);

	if (stat(filename, &stat_file) == -1)
	{
		printf("\nInvalid filename!\n");
		return -1;
	}
	int mode = stat_file.st_mode;
	int mask = 0x1ff;
	mode &= mask;

	printf("\n%s\n", filename);
	print_bin(mode);
	print_alph(mode);
	print_digit(oct_to_dec(mode));
	return mode;
}

void set_stat()
{
	printf("\nchmod ");
	char chmod[LEN_CHMOD];
	fgets(chmod, LEN_CHMOD, stdin);

	char perm[LEN_CHMOD];
	char filename[LEN_FILE];
	sscanf(chmod, "%s%s", perm, filename);

	int mode = get_stat(filename);
	if (mode == -1)
		return;

	if (atoi(perm) != 0)
	{
		printf("\nNew permission:\n%s\n", filename);
		int result_oct = atoi(perm);
		int result_dec = oct_to_dec(result_oct);
		print_bin(result_dec);
		print_alph(result_dec);
		print_digit(result_oct);
		return;
	}
	char usr[] = "ogu";
	char act[] = "+-=";
	char prm[] = "xwr";

	int offset = 0;
	char action;
	int num_prm = 0;
	for (int i = 0; i < strlen(perm); i++)
	{
		for (int j = 0; j < strlen(usr); j++)
		{
			if (perm[i] == usr[j])
				offset = j;
			if (perm[i] == act[j])
				action = act[j];
			if (perm[i] == prm[j])
				num_prm |= (1 << j);
		}
	}
	switch (action)
	{
		case '-':
			mode &= ~(num_prm << (3 * offset));
			break;
		case '+':
			mode |= (num_prm << (3 * offset));
			break;
		case '=':
			mode &= ~(7 << (3 * offset));
			mode |= (num_prm << (3 * offset));
			break;
	}
	printf("\nNew permission:\n%s\n", filename);
	print_bin(mode);
	print_alph(mode);
	print_digit(mode);
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

void print_digit(int mode)
{
	printf("Digit format: %d\n", mode);
}
