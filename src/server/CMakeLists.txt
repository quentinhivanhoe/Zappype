cmake_minimum_required(VERSION 3.26)

project(zappy_server LANGUAGES C)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)

add_executable(zappy_server
    ./main.c
    ./network/clean_server.c
    ./parsing/handle_flags.c
    ./parsing/handle_flags2.c
    ./network/setup_server.c
    ./network/handle_clients.c
    ./logical/is_num.c
    ./parsing/retrieve_flags.c
    ./network/signal.c
    ./network/registration.c
    ./gui.c
    ./gui_commands.c
)

target_include_directories(zappy_server PRIVATE includes)

set_target_properties(zappy_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../..)