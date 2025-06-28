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

$(SERVER): $(AI) $(GUI)
	@echo "Building Server..."
	mkdir -p build
	mkdir -p build/Server
	cd build/Server && cmake ../.. && make
	@echo "Server built successfully."
	cd ../..

$(AI):
	@echo "Building AI..."
	make -C ./src/ai
	mv src/ai/$(AI) .

$(GUI):
	@echo "Building GUI..."

all: $(AI) $(SERVER) $(GUI)

clean:
	rm -rf build
	make -C ./src/ai clean

fclean: clean
	rm -rf $(SERVER)
	rm -rf $(AI)
	rm -rf $(GUI)

re: fclean all

.PHONY: $(SERVER) $(AI) $(GUI) all clean fclean re
