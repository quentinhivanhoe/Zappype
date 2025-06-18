##
## EPITECH PROJECT, 2025
## B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
## File description:
## Makefile
##

SRC = $(shell find . -type f -name "*.c")

OBJ = $(SRC:.c=.o)

NAME = zappy_server

DFLAGS	= -g -ggdb -g3

CFLAGS = -Wall -Wextra -Werror -I./includes

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(OBJ)

debug:
	$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)
	rm -rf *.log

fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
