SRC= ft_dprintf.c ft_dprintf_utils.c

OBJS=$(SRC:.c=.o)
AR=ar -rcs
NAME=libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

%.o:%.c
	@i386-elf-gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	@rm -rf *.o

fclean:
	@rm -rf *.o libft.a

re:fclean all

.PHONY: all clean fclean re