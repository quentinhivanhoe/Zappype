cmake_minimum_required(VERSION 3.26)
project(zappy_server LANGUAGES C)

add_compile_options(
    -Wall
    -Wextra
    -Werror
)

file(GLOB_RECURSE CODE_FILES "./*.c")

add_executable(zappy_server ${CODE_FILES})

target_link_libraries(zappy_server m)

target_include_directories(zappy_server PRIVATE includes)

set_target_properties(zappy_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../../"
)
