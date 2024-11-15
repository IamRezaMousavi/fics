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

#include <stdlib.h>

#include "common.h"
#include "iset.h"
#include "utils.h"

PUBLIC int
com_iset(int p, param_list param)
{
	if (param[0].type != TYPE_WORD ||
	    param[1].type != TYPE_WORD) {
		pprintf(p, "%s: bad parameters\n", __func__);
		return COM_BADPARAMETERS;
	}

	pprintf(p, "%s: %s %s\n", __func__,
	    param[0].val.word,
	    param[1].val.word);
	return COM_OK;
}
