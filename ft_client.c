#include "minitlak.h"

void	send_char(pid_t pid, int c)
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

void	send_str(pid_t pid, char *str)
{
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
	{
		ft_printf("ok\n");
		exit(EXIT_SUCCESS);
	}
}

void	set_sigaction(struct sigaction *act)
{
	ft_bzero(act, sizeof(*act));
	sigemptyset(&(act->sa_mask));
	sigaddset(&(act->sa_mask), SIGUSR1);
	sigaddset(&(act->sa_mask), SIGUSR2);
	act->sa_flags = SA_SIGINFO;
	act->sa_sigaction = signal_handler;
	sigaction(SIGUSR1, act, NULL);
	sigaction(SIGUSR2, act, NULL);
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	pid_t				pid;

	if (argc != 3)
	{
		ft_printf("wrong argc");
		return (1);
	}
	set_sigaction(&act);
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
	return (0);
}
