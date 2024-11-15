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

#ifndef _RATINGCONV_H
#define _RATINGCONV_H

#include "command.h"     /* param_list */

extern int com_CONVERT_BCF(int, param_list);
extern int com_CONVERT_ELO(int, param_list);
extern int com_CONVERT_USCF(int, param_list);

#endif    /* _RATINGCONV_H */
