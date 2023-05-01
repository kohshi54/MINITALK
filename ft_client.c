/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:10:22 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/01 17:15:42 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char(pid_t pid, int c)
{
	ssize_t	i;

	i = 7;
	while (0 <= i)
	{
		if (c & (1 << i))
			ft_kill(pid, SIGUSR1);
		else
			ft_kill(pid, SIGUSR2);
		(void)pause();
		i--;
	}
}

static void	send_str(pid_t pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, EOT);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
	{
		ft_printf("ok\n");
		exit(EXIT_SUCCESS);
	}
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
	set_sigaction(&act, signal_handler);
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
	return (0);
}
