#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "func.h"

/*-----------------------------------------*/
// Secondary functions;
/*-----------------------------------------*/
static void clear_input()
{
	for (char c = getchar(); c != '\n'; c = getchar());
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

static int enter_alph_format(char *perm)
{
	printf("\nEnter permission in alphabetic format: ");
	fgets(perm, LEN_BITS + 1, stdin);
	clear_input();
	if (strlen(perm) < 9)
	{
		printf("Wrong format!\n");
		return -1;
	}

	int result = alph_mode_to_bin(perm);
	if (result == -1)
		return -1;

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

	int tmp = *perm;
	while (tmp > 0)
	{
		if (tmp % 10 < 4 && tmp % 10 != 0)
		{
			printf("Invalid permission!\n");
			return -1;
		}
	}

	int result = digit_mode_to_bin(*perm);
	print_bin(result);
	return 1;

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

/*-----------------------------------------*/
// Main functions;
/*-----------------------------------------*/
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

int alph_mode_to_bin(char* permission)
{
	int mode = 0;
	int index = LEN_BITS - 1;
	int isInvalid = 0;
	for (int i = 0; i < LEN_BITS;  i++)
	{
		char p = permission[i];
		if (p != 'r' && p != 'w' && p != 'x' && p != '-')
		{
			printf("Invalid permission!\n");
			return -1;
		}

		if (p != '-')
			mode |= (1 << index);
		index--;
	}

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
	int mask = 0777;
	mode &= mask;

	printf("\n%s\n", filename);
	print_bin(mode);
	print_alph(mode);
	print_digit(mode);
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
		int p = atoi(perm);
		if (p < 100 || p > 1000)
		{
			printf("Wrong format!\n");
			return;
		}

		while (p > 0)
		{
			if (p % 10 < 4 && p % 10 != 0)
			{
				printf("Invalid permission!\n");
				return;
			}
		}

		printf("\nNew permission:\n%s\n", filename);
		int result = oct_to_dec(atoi(perm));
		print_bin(result);
		print_alph(result);
		print_digit(result);
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

/*-----------------------------------------*/
// Print functions;
/*-----------------------------------------*/
void print_bin(int mode)
{
	printf("Binary format: ");
	char res[LEN_BITS] = "000000000";
	for (int i = 0; i < LEN_BITS; i++)
	{
		res[sizeof(res) - 1 - i] = (mode % 2) ? '1' : '0';
		mode /= 2;
	}
	printf("%s\n", res);
}

void print_alph(int mode)
{
	char alph[LEN_BITS];
	strncpy(alph, "rwxrwxrwx", LEN_BITS);
	printf("Alphabet format: ");

	char res[LEN_BITS] = "000000000";
	for (int i = 0; i < LEN_BITS; i++)
	{
		res[sizeof(res) - 1 - i] = (mode % 2) ? '1' : '0';
		mode /= 2;
	}

	for (int i = 0; i < LEN_BITS; i++)
		(res[i] == '1') ? printf("%c", alph[i]) : printf("-");

	printf("\n");
}

void print_digit(int mode)
{
	printf("Digit format: %o\n", mode);
}
