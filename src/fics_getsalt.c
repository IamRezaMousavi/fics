/*
 * Written by Markus Uhlin <maxxe@rpblc.net>,
 * 25 Dec 2023.
 */

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fics_getsalt.h"

char *
fics_getsalt(void)
{
	static bool init_done = false;
	static const char legal_index[] =
	    "./0123456789"
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	    "abcdefghijklmnopqrstuvwxyz";
	static char salt[FICS_SALT_SIZE];

	if (!init_done) {
		strcpy(salt, FICS_SALT_BEG);
		init_done = true;
	}

	srand(time(NULL));

	/* CPP */
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<size_t> dist(0, strlen(legal_index) - 1);

	size_t legal_index_len = strlen(legal_index);
	for (size_t i = 7; i < sizeof salt; i++)
	{
		salt[i] = legal_index[rand() % legal_index_len];
	}
	salt[sizeof salt - 1] = '\0';
	return (&salt[0]);
}

#if SELF_TEST
int
main(void)
{
	puts(fics_getsalt());
	puts(fics_getsalt());
	puts(fics_getsalt());
	return 0;
}
#endif
