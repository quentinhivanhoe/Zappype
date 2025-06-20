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
	make -C ./src/ai
	mv src/ai/$(AI) .

$(GUI):
	@echo "Building GUI..."

clean:
	rm -rf build
	make -C ./src/ai clean

fclean: clean
	rm -rf $(SERVER)
	rm -rf $(AI)
	rm -rf $(GUI)

re: fclean all

.PHONY: all clean fclean re $(SERVER) $(AI) $(GUI)
