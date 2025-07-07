##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Makefile
##

NAME = zappy_gui

RESSOURCES_SOURCE = ressources
RESSOURCES_TARGET = ./assets
DOXYGEN_FILE = Doxyfile.txt
DOCUMENTATION_DIR = doc

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -Iincludes -fno-gnu-unique
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -ldl

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)
	@cp -r $(RESSOURCES_SOURCE) $(RESSOURCES_TARGET)

clean:
	rm -rf $(OBJ)
	rm -rf $(DOCUMENTATION_DIR)

fclean: clean
	rm -rf $(RESSOURCES_TARGET)
	rm -rf $(NAME)

re: fclean all

doc:
	@mkdir $(DOCUMENTATION_DIR)
	@doxygen $(DOXYGEN_FILE)
	@rm -rf doc/latex

.PHONY: all clean fclean re doc
