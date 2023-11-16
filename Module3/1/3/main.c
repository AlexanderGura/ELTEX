#include <stdlib.h>
#include "func.h"

int main(int argc, char *argv[])
{
	char filename[FILE_LEN];
	char args[ARG_LEN];
	char *arguments[ARG_CON];

	get_filename(filename);
	get_args(args, arguments);
	execute(filename, arguments);

	exit(EXIT_SUCCESS);
}
