#include <unistd.h>
#include <stdio.h>
#include "LIBFT/libft.h"
#include <signal.h>
#include "FT_PRINTF/ft_printf.h"
//  cc -o client ft_client.c LIBFT/ft_atoi.c LIBFT/ft_isdigit.c FT_PRINTF/ft_printf.c FT_PRINTF/ft_printf_utils.c FT_PRINTF/ft_convert_base.c

void    send_char(pid_t pid, int c)
{
	unsigned char   byte;
	size_t			i;

	i = 0;
	byte = 1 << 7;
	while (i < 8)
	{
		if (c & byte)
		{
			// ft_printf("1");
			kill(pid, SIGUSR1);
		}

		else
		{
			// ft_printf("0");
			kill(pid, SIGUSR2);
		}
		byte = byte >> 1;
		i++;
		usleep(100);
	}
}

void    send_str(pid_t pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
}

void signal_handler(int signal, siginfo_t *info, void *context)
{
	ft_printf("ok\n");
}

void set_signal_action(struct sigaction *sa)
{
	ft_bzero(sa, sizeof(*sa));
	(*sa).sa_flags = SA_SIGINFO;
	(*sa).sa_sigaction = &signal_handler; // ポインタにするのかしないのか
	sigaction(SIGUSR1, sa, NULL);
	// sigaction(SIGUSR2, sa, NULL);
}

int main(int argc, char *argv[])
{
	pid_t   pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("wrong argc");
		return (1);
	}
	set_signal_action(&sa);
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
	return (0);
}
