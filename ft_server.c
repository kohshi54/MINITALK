#include "minitlak.h"

volatile signalinfo_t	g_clientinfo;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	g_clientinfo.pid = info->si_pid;
	if (signum == SIGUSR1)
		g_clientinfo.signal_num = 1;
	else if (signum == SIGUSR2)
		g_clientinfo.signal_num = 0;
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

void	send_back_signal(int signum)
{
	usleep(60);
	kill(g_clientinfo.pid, signum);
}

int	main(void)
{
	struct sigaction	act;
	char				byte;
	size_t				i;

	ft_printf("pid: %d\n", getpid());
	set_sigaction(&act);
	byte = 0;
	i = 0;
	while (1)
	{
		(void)pause();
		byte = byte << 1;
		byte = byte | g_clientinfo.signal_num;
		if (++i == 8)
		{
			if (byte == '\0')
				send_back_signal(SIGUSR2);
			else
				write(STDOUT_FILENO, &byte, sizeof(char));
			i = 0;
			byte = 0;
		}
		send_back_signal(SIGUSR1);
	}
	return (0);
}
