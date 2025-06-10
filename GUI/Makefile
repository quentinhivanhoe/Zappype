##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Makefile
##

NAME = zappy_gui

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror -fno-gnu-unique -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

SRC = $(shell find -name "*.cpp")

OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	g++ $(CPPFLAGS) -ldl -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re