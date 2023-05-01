#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "LIBFT/libft.h"
# include "FT_PRINTF/ft_printf.h"

typedef struct signalinfo
{
	volatile sig_atomic_t pid;
	volatile sig_atomic_t signal_num;

} signalinfo_t ;

#endif