#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "LIBFT/libft.h"
# include "FT_PRINTF/ft_printf.h"

# define EOT 4

void	ft_putchar_err(char c);
void	ft_kill(pid_t pid, int signum);
void	set_sigaction(struct sigaction *act, void (*signal_handler)(int signum, siginfo_t *info, void *context));

typedef struct signalinfo
{
	volatile sig_atomic_t pid;
	volatile sig_atomic_t signal_num;

} signalinfo_t ;

#endif