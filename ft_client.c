#include <unistd.h>
#include <stdio.h>
#include "LIBFT/libft.h"
#include "FT_PRINTF/ft_printf.h"
#include <signal.h>
//cc -o client ft_client.c LIBFT/ft_atoi.c LIBFT/ft_isdigit.c FT_PRINTF/ft_printf.c FT_PRINTF/ft_printf_utils.c FT_PRINTF/ft_convert_base.c LIBFT/ft_bzero.c

void    send_char(pid_t pid, int c)
{
	ssize_t	i;

	i = 7;
	while (0 <= i)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		usleep(60);
		i--;
	}
}

void    send_str(pid_t pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

void signal_handler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGUSR2)
	{
		ft_printf("ok\n");
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char *argv[])
{
	struct sigaction	act;
	pid_t				pid;

	if (argc != 3)
	{
		ft_printf("wrong argc");
		return (1);
	}

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signal_handler;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);

	pause();

	return (0);
}
