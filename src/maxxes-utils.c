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

#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if __linux__
#include <bsd/string.h>
#endif

#include "maxxes-utils.h"

void
snprintf_trunc_chk(const char *file, const long int line,
    char *str, size_t size, const char *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = vsnprintf(str, size, format, ap);
	va_end(ap);

	if (ret < 0 || (size_t)ret >= size)
		warnx("%s:%ld: warning: vsnprintf() truncated", file, line);
}

void
strlcpy_trunc_chk(char *dst, const char *src, size_t dstsize,
    const char *file,
    const long int line)
{
	if (strlcpy(dst, src, dstsize) >= dstsize)
		warnx("%s:%ld: warning: strlcpy() truncated", file, line);
}

void
strlcat_trunc_chk(char *dst, const char *src, size_t dstsize,
    const char *file,
    const long int line)
{
	if (strlcat(dst, src, dstsize) >= dstsize)
		warnx("%s:%ld: warning: strlcat() truncated", file, line);
}
