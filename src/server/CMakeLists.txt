cmake_minimum_required(VERSION 3.26)

project(zappy_server LANGUAGES C)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)

add_executable(zappy_server
    ./main.c
    ./clean_server.c
    ./handle_flags.c
    ./handle_flags2.c
    ./setup_server.c
    ./handle_clients.c
    ./is_num.c
    ./retrieve_flags.c
    ./signal.c
)

target_include_directories(zappy_server PRIVATE includes)

set_target_properties(zappy_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../..)