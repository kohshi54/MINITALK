/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:12:27 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/01 17:13:58 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	set_sigaction(struct sigaction *act, void (*signal_handler)\
						(int signum, siginfo_t *info, void *context));

typedef struct signalinfo
{
	volatile sig_atomic_t	pid;
	volatile sig_atomic_t	signal_num;

}	t_signalinfo;

#endif
