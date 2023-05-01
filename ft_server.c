/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:10:47 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/01 17:15:27 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile t_signalinfo	g_clientinfo;

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	g_clientinfo.pid = info->si_pid;
	if (signum == SIGUSR1)
		g_clientinfo.signal_num = 1;
	else if (signum == SIGUSR2)
		g_clientinfo.signal_num = 0;
}

int	main(void)
{
	struct sigaction	act;
	char				byte;
	size_t				i;

	ft_printf("pid: %d\n", getpid());
	set_sigaction(&act, signal_handler);
	byte = 0;
	i = 0;
	while (1)
	{
		(void)pause();
		byte = byte << 1;
		byte = byte | g_clientinfo.signal_num;
		if (++i == 8)
		{
			if (byte == EOT)
				ft_kill(g_clientinfo.pid, SIGUSR2);
			else
				ft_putchar_err(byte);
			i = 0;
			byte = 0;
		}
		ft_kill(g_clientinfo.pid, SIGUSR1);
	}
	return (0);
}
