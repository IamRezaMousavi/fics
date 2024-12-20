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

#ifndef _FICSPATHS_H_
#define _FICSPATHS_H_

#include "config.h"

#define DEFAULT_ADHELP        PREFIX "/data/admin"
#define DEFAULT_ADJOURNED     PREFIX "/games/adjourned"
#define DEFAULT_BOARDS        PREFIX "/data/boards"
#define DEFAULT_BOOK          PREFIX "/data/book"
#define DEFAULT_COMHELP       PREFIX "/data/com_help"
#define DEFAULT_CONFIG        PREFIX "/config"
#define DEFAULT_HELP          PREFIX "/data/help"
#define DEFAULT_HISTORY       PREFIX "/games/history"
#define DEFAULT_INDEX         PREFIX "/data/index"
#define DEFAULT_INFO          PREFIX "/data/info"
#define DEFAULT_JOURNAL       PREFIX "/games/journal"
#define DEFAULT_LISTS         PREFIX "/data/lists"
#define DEFAULT_MESS          PREFIX "/data/messages"
#define DEFAULT_NEWS          PREFIX "/data/news"
#define DEFAULT_PLAYERS       PREFIX "/players"
#define DEFAULT_SOURCE        PREFIX "/FICS"
#define DEFAULT_STATS         PREFIX "/data/stats"
#define DEFAULT_USAGE         PREFIX "/data/usage"
#define DEFAULT_USCF          PREFIX "/data/uscf"

#define HELP_DANISH      PREFIX "/data/Danish"
#define HELP_FRENCH      PREFIX "/data/French"
#define HELP_SPANISH     PREFIX "/data/Spanish"

#define MESS_FULL        PREFIX "/data/messages/full"
#define MESS_FULL_UNREG  PREFIX "/data/messages/full_unreg"

#define USAGE_DANISH     PREFIX "/data/usage_danish"
#define USAGE_FRENCH     PREFIX "/data/usage_french"
#define USAGE_SPANISH    PREFIX "/data/usage_spanish"

#define DAEMON_LOCKFILE	PREFIX "/fics.pid"
#define DAEMON_LOGFILE PREFIX "/fics.log"

#endif /* _FICSPATHS_H */
