/*
    fics - An internet chess server.
    Copyright (C) 2023 Markus Uhlin

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#ifndef _SHUTDOWN_H
#define _SHUTDOWN_H

#include <stdbool.h>

#include "command.h" /* param_list */
#include "common.h" /* __dead */

extern bool	 check_and_print_shutdown(int);
extern int	 com_shutdown(int, param_list);
extern int	 com_whenshut(int, param_list);
extern int	 server_shutdown(int, char *);

extern __dead void ShutDown(void);

extern void	 ShutHeartBeat(void);
extern void	 output_shut_mess(void);

#endif /* _SHUTDOWN_H */
