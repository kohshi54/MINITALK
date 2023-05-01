NAME = minitalk
NAME_CLIENT = client
NAME_SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS_CLIENT = ft_client.c
SRCS_SERVER = ft_server.c

OBJS_CLIENT = $(SRCS_CLIENT:%.c=%.o)
OBJS_SERVER = $(SRCS_SERVER:%.c=%.o)

LIBFT = libft.a
LIBFT_DIR = LIBFT/

FT_PRINTF = ft_printf.a
FT_PRINTF_DIR = FT_PRINTF/

INCLUDES = minitalk.h

LIBRARY = -L./$(LIBFT_DIR) -lft -L./$(FT_PRINTF_DIR) -lftprintf

all : $(NAME)

$(NAME) : $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJS_CLIENT) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBRARY) -o $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJS_SERVER) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBRARY) -o $(NAME_SERVER)

$(LIBFT) : 
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF) :
	$(MAKE) -C $(FT_PRINTF_DIR)

clean :
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean : clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

re : fclean all

.PHONY : clean fclean re all

.SECONDARY : 