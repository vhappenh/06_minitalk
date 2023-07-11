NAME_S := server

NAME_C := client

LIBFT := ./libft_ultra/libft.a

CFLAGS := -Wall -Werror -Wextra -g

SRC_S := server.c

SRC_C := client.c

OBJ_S := $(SRC_S:.c=.o)

OBJ_C := $(SRC_C:.c=.o)

S_C := $(NAME_S) $(NAME_C)

all: $(S_C)

$(NAME_S): $(OBJ_S)
	$(MAKE) all -C ./libft_ultra
	cc -o $(NAME_S) $(OBJ_S) $(LIBFT)

$(NAME_C): $(OBJ_C)
	$(MAKE) all -C ./libft_ultra
	cc -o $(NAME_C) $(OBJ_C) $(LIBFT)

clean:
	$(MAKE) clean -C ./libft_ultra
	rm -f $(OBJ_S)
	rm -f $(OBJ_C)

fclean:	clean
	$(MAKE) fclean -C ./libft_ultra
	rm -f $(NAME_S)
	rm -f $(NAME_C)

re: 	fclean all

phony: all clean fclean re
