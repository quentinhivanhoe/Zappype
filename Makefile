##
## EPITECH PROJECT, 2025
## B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
## File description:
## Makefile
##

NAME		=	zappy

SERVER = zappy_server

AI = zappy_ai

GUI = zappy_gui

$(SERVER):
	@echo "Building Server..."
	mkdir -p build
	mkdir -p build/Server
	cd build/Server && cmake ../.. && make
	@echo "Server built successfully."
	cd ../..

all: $(SERVER) $(AI) $(GUI)

$(AI):
	@echo "Building AI..."

$(GUI):
	@echo "Building GUI..."

clean:
	rm -rf build

fclean: clean
	rm -rf $(SERVER)

re: fclean all

.PHONY: all clean fclean re $(SERVER) $(AI) $(GUI)
