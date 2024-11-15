/*
    fics - An internet chess server.
    Copyright (C) 1993  Richard V. Nash

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#ifndef _ECO_H
#define _ECO_H

#include "command.h" /* param_list */

#define SPACE_CHK()\
	do {\
		if (space > 0) {\
			FENstring[FENcount++] = (space + '0');\
			space = 0;\
		}\
	} while (0)

typedef struct {
	char	ECO[4];
	char	FENpos[80];
} ECO_entry;

typedef struct {
	char	NIC[6];
	char	FENpos[80];
} NIC_entry;

typedef struct {
	char	LONG[80];
	char	FENpos[80];
} LONG_entry;

extern char	*boardToFEN(int);
extern char	*getECO(int);
extern int	 com_eco(int, param_list);
extern void	 BookInit(void);
extern void	 ECO_init(void);
extern void	 LONG_init(void);
extern void	 NIC_init(void);

#endif
