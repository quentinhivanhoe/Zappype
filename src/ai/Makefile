##
## EPITECH PROJECT, 2025
## Zappype
## File description:
## Makefile
##

MAIN = main.py
NAME = zappy_ai

$(NAME):
	chmod +x $(MAIN)
	cp main.py $(NAME)

all: $(NAME)

clean:
	rm -rf __pycache__

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)
