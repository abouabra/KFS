SRC= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_toupper.c \
        ft_tolower.c ft_memset.c ft_bzero.c ft_memcpy.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
        ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
        ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_itoa.c ft_split.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
        ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		gnl.c gnl_utils.c \
		ft_dprintf.c ft_dprintf_utils.c my_alloc.c

SRC_DIR = src/
OBJ_DIR = obj/

OBJS= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INCLUDES = -I includes/

AR=ar -rcs
NAME=libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@i386-elf-gcc -Wall -Wextra -Werror -c $(INCLUDES) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(OBJ_DIR) libft.a

re:fclean all

.PHONY: all clean fclean re