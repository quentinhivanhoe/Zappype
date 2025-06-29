##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Makefile
##

NAME = zappy_gui

RESSOURCES_SOURCE = ressources

RESSOURCES_TARGET = ./assets

CPPFLAGS = -std=c++20 -Wall -Iincludes -Wextra -Werror -fno-gnu-unique -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

SRC = $(shell find -name "*.cpp")

OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	@g++ $(CPPFLAGS) -ldl -o $(NAME) $(OBJ)
	@cp -r $(RESSOURCES_SOURCE) $(RESSOURCES_TARGET)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(RESSOURCES_TARGET)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re