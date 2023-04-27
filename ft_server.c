#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "FT_PRINTF/ft_printf.h"
#include "LIBFT/libft.h"

//cc -Wall -Wextra -Werror ft_server.c FT_PRINTF/ft_printf.c FT_PRINTF/ft_convert_base.c FT_PRINTF/ft_printf_utils.c

#include <stdlib.h>
#include <unistd.h>

// volatile sig_atomic_t flag = 0;
volatile sig_atomic_t byte = 0;

void signal_handler(int signal, siginfo_t *info, void *context)
{
	volatile static sig_atomic_t i;
	char c;
	
	(void)context;
	if (signal == SIGUSR1)
		byte = byte | 1;
	// ft_printf("byte: %d\n", byte);
	if (i == 7)
	{
		c = byte;
		write(STDOUT_FILENO, &c, 1);
		i = 0;
		byte = 0;
		// flag = 1;
		// ft_printf("received from pid: %d\n", (int)info->si_pid);
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		i++;
		byte = byte << 1;
	}
}

void set_signal_action(struct sigaction *sa)
{
	ft_bzero(sa, sizeof(*sa));
	(*sa).sa_flags = SA_SIGINFO;
	(*sa).sa_sigaction = &signal_handler; // ポインタにするのかしないのか
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
}

int main()
{
	struct sigaction	sa;

	ft_printf("pid: %d\n", getpid());
	set_signal_action(&sa);
	while (1)
	{
		// printf("Wasting your cycles: %d\n", getpid());
		// if (flag)
		// {
			// ft_printf("\nreceived signal\n");
			// flag = 0;
		// }
			
		// sleep(1);
		pause();
	}
	// pause();
}
