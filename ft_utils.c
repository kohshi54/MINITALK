/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:10:38 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/01 17:17:50 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_kill(pid_t pid, int signum)
{
	usleep(60);
	if (kill(pid, signum) == -1)
		exit(EXIT_FAILURE);
}

void	ft_putchar_err(char c)
{
	if (write(STDOUT_FILENO, &c, sizeof(char)) == -1)
		exit(EXIT_FAILURE);
}

void	set_sigaction(struct sigaction *act, void (*signal_handler) \
						(int signum, siginfo_t *info, void *context))
{
	ft_bzero(act, sizeof(*act));
	sigemptyset(&(act->sa_mask));
	sigaddset(&(act->sa_mask), SIGUSR1);
	sigaddset(&(act->sa_mask), SIGUSR2);
	act->sa_flags = SA_SIGINFO;
	act->sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, act, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, act, NULL) == -1)
		exit(EXIT_FAILURE);
}
