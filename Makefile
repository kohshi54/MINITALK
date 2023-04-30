NAME = minitalk
NAME_CLIENT = client
NAME_SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_CLIENT = ft_client.c
SRCS_SERVER = ft_server.c

OBJS_CLIENT = $(SRCS_CLIENT:%.c=%.o)
OBJS_SERVER = $(SRCS_SERVER:%.c=%.o)

LIBRARY = -L./$(LIBFT_DIR) -lft -L./$(FT_PRINTF_DIR) -lftprintf

LIBFT = libft
LIBFT_DIR = LIBFT/

FT_PRINTF = ft_printf
FT_PRINTF_DIR = FT_PRINTF/

INCLUDES = minitalk.h

all : $(NAME)

$(NAME) : $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJS_CLIENT) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(SRCS_CLIENT) $(LIBRARY) -o $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJS_SERVER) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(SRCS_SERVER) -L./$(LIBFT_DIR) -lft -L./$(FT_PRINTF_DIR) -lftprintf -o $(NAME_SERVER)

# $(LIBRARY) : $(LIBFT) $(FT_PRINTF)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF) :
	$(MAKE) -C $(FT_PRINTF_DIR)

clean :
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean : clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re : fclean all

.PHONY: clean fclean re all