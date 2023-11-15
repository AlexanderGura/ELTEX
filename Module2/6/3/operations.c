#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "operations.h"

static void clear_input(void)
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

static char* prepare_path(const char *path)
{
	char *temp = (char*)malloc(strlen(path) + ADD_SYM);
	if (temp == NULL)
		exit(EXIT_FAILURE);

	strncpy(temp, "libs/lib", 10);
	strncat(temp, path, strlen(path));
	strncat(temp, ".so", 4);

	return temp;
}

static void clear_path(char *path)
{
	free(path);
}

static void get_function(const char *operation)
{
	char *filename = prepare_path(operation);

	void *handle = dlopen(filename, RTLD_LAZY);
	if (handle == NULL)
	{
		fputs(dlerror(), stderr);
		exit(EXIT_FAILURE);
	}

	void (*oper)(void) = dlsym(handle, operation);
	if (oper == NULL)
	{
		fputs(dlerror(), stderr);
		exit(EXIT_FAILURE);
	}
	oper();

	char *error = dlerror();
	if (error != NULL)
	{
		fprintf(stderr, "%s", error);
		exit(EXIT_FAILURE);
	}

	dlclose(handle);
	clear_path(filename);
}

static int select_choice(char choice)
{
	switch(choice)
	{
		case '1':
		case '+':
			get_function("add");
			return 1;
		case '2':
		case '-':
			get_function("sub");
			return 1;
		case '3':
		case '*':
			get_function("mult");
			return 1;
		case '4':
		case '/':
			get_function("div");
			return 1;
		case '5':
		case '^':
			get_function("power");
			return 1;
		case '6':
		case 'r':
			get_function("sqroot");
			return 1;
		case '7':
		case 'l':
			get_function("natlog");
			return 1;
		case '0':
		case 'q':
		case 'Q':
			printf("Good bye, have a good day!\n");
			return 0;
		default:
			printf("Invalid choice!\n");
			return -1;
		}
}

int menu()
{
	printf("\nEnter '0' or 'q' to end the calc!\n");
	printf("Enter the number of operation:\n");
	printf("1(+). +\n2(-). -\n3(*). *\n4(/). /\n");
	printf("5(^). power\n6(r). sqrt\n7(l). ln\n");
	printf("Your choice: ");

	char choice;
	choice = getchar();
	clear_input();

	return select_choice(choice);
}
