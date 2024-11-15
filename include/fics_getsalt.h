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

#ifndef FICS_GETSALT_H
#define FICS_GETSALT_H

#define FICS_SALT_BEG	"$2b$10$"
#define FICS_SALT_SIZE	30

#ifdef __cplusplus
extern "C" {
#endif

char *fics_getsalt(void);

#ifdef __cplusplus
}
#endif

#endif
