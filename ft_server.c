#include <signal.h>
#include <stdio.h>
#include "FT_PRINTF/ft_printf.h"
#include "LIBFT/libft.h"
#include <stdlib.h>
//cc -Wall -Wextra -Werror -o server ft_server.c FT_PRINTF/ft_printf.c FT_PRINTF/ft_convert_base.c FT_PRINTF/ft_printf_utils.c LIBFT/ft_bzero.c 

volatile sig_atomic_t byte = 0;

void signal_handler(int signum, siginfo_t *info, void *context)
{
	volatile static sig_atomic_t i = 0;
	volatile sig_atomic_t c;
	
	(void)context;
	byte = byte << 1;
	if (signum == SIGUSR1)
		byte = byte | 1;
	if (++i == 8)
	{
		c = 0xff & byte;
		if (c == '\0')
		{
			usleep(60);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(STDOUT_FILENO, (char *) &c, sizeof(char));
		i = 0;
		byte = 0;
	}
	usleep(60);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("pid: %d\n", getpid());

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signal_handler;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	while (1)
		(void)pause();

	return (0);
}
