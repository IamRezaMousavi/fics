/* shutdown.h */

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
