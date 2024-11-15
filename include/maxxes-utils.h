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

#ifndef MAXXES_UTILITIES_H
#define MAXXES_UTILITIES_H

#include <stddef.h>

#include "common.h"

#define msnprintf(p_str, p_size, ...) \
	snprintf_trunc_chk(__FILE__, __LINE__, (p_str), (p_size), __VA_ARGS__)
#define mstrlcpy(p_dst, p_src, p_dstsize) \
	strlcpy_trunc_chk((p_dst), (p_src), (p_dstsize), __FILE__, __LINE__)
#define mstrlcat(p_dst, p_src, p_dstsize) \
	strlcat_trunc_chk((p_dst), (p_src), (p_dstsize), __FILE__, __LINE__)

void	snprintf_trunc_chk(const char *file, const long int line,
	    char *str, size_t size, const char *format, ...) PRINTFLIKE(5);
void	strlcpy_trunc_chk(char *dst, const char *src, size_t dstsize,
	    const char *, const long int);
void	strlcat_trunc_chk(char *dst, const char *src, size_t dstsize,
	    const char *, const long int);

#endif
