/*
    fics - An internet chess server.
    Copyright (C) 2024  Reza Mousavi

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

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
