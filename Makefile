NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
# FT_PRINTF = ./ft_printf/libftprintf.a
LIBFT = ./includes/libft/libft.a

SRCS = minishell.c\
	free.c builts_in.c utils.c \
	./built_ins/echo.c\
	./built_ins/exit.c\
	./built_ins/pwd.c \
	./garbage_utiles.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "clean done"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean done"

re: fclean all
	@echo "re done" 

.PHONY: all clean fclean re