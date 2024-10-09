#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

static void
usage(char const* app)
{
	fprintf(stderr, "uasge: %s [fics | add-player | make-rank] [options]\n", app);
	exit(1);
}

int
main(int argc, char **argv)
{
	if(argc < 2)
		usage(argv[0]);

	if(strcmp(argv[1], "fics") == 0)
		fics_main(argc - 1, argv + 1);
	else if(strcmp(argv[1], "add-player") == 0)
		add_player_main(argc - 1, argv + 1);
	else if(strcmp(argv[1], "make-rank") == 0)
		make_rank_main(argc - 1, argv + 1);
	else
		usage(argv[0]);

	return 0;
}
