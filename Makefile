##
## EPITECH PROJECT, 2025
## B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
## File description:
## Makefile
##

NAME = zappy

SERVER = zappy_server
GUI = zappy_gui
AI = zappy_ai

BUILD_DIR = build

all: $(AI) $(SERVER) $(GUI)

$(AI):
	@echo "Building AI..."
	$(MAKE) -C ./src/ai
	@mv -f ./src/ai/$(AI) .

$(SERVER):
	@echo "Building Server..."
	mkdir -p $(BUILD_DIR)/server
	cmake -S ./src/server -B $(BUILD_DIR)/server -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$(PWD)"
	$(MAKE) -C $(BUILD_DIR)/server
	@echo "Server built successfully."

$(GUI):
	@echo "Building GUI..."
	mkdir -p $(BUILD_DIR)/gui
	cmake -S ./src/gui -B $(BUILD_DIR)/gui -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$(PWD)"
	$(MAKE) -C $(BUILD_DIR)/gui
	@echo "GUI built successfully."

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C ./src/ai clean

fclean: clean
	rm -f $(SERVER) $(GUI) $(AI)
	rm -rf ./assets

re: fclean all

.PHONY: all clean fclean re $(SERVER) $(GUI) $(AI)
