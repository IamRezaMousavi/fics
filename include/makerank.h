/*
    fics - An internet chess server.
    Copyright (C) 2024 Markus Uhlin

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#ifndef MAKERANK_H
#define MAKERANK_H

#include "config.h"

#define COMPUTER_FILE	DEFAULT_LISTS "/computer"
#define MAX_LOGIN_NAME	21

typedef struct _ratings {
	int	num;
	int	rating;
} ratings;

typedef struct _Entry {
	char	name[MAX_LOGIN_NAME];
	int	computer;
	ratings	r[4];
} ENTRY;

#endif
