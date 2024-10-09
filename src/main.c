#include <stdio.h>
#include <string.h>

#include "main.h"

static void print_usage(char const* app)
{
    fprintf(stderr, "uasge: %s [fics | add-player | make-rank] [options]\n", app);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "fics") == 0)
        fics_main(argc - 1, argv + 1);
    else if(strcmp(argv[1], "add-player") == 0)
        add_player_main(argc - 1, argv + 1);
    else if(strcmp(argv[1], "make-rank") == 0)
        make_rank_main(argc - 1, argv + 1);

    else
        print_usage(argv[0]);
}