##
## EPITECH PROJECT, 2025
## B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
## File description:
## Makefile
##

SRC 	= $(shell find ./src -type f -name "*.c")
OBJ 	= $(SRC:.c=.o)
NAME 	= zappy_server
CFLAGS 	= -Wall -Wextra -Werror -I./includes
BUILD	= Dev

all: $(NAME)

$(NAME): $(OBJ) $(BUILD)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@mv $(OBJ) $(BUILD)

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
