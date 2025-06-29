/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** main
*/

#include "./includes/server.h"

int main(int argc, char **argv)
{
    my_server()->info.fd_count = 0;
    if (argc > 1) {
        my_server()->info.port = atoi(argv[1]);
    }
    if (setup_server() < 0)
        return EXIT_FAILURE;
    printf("Server listening on port %d...\n", my_server()->info.port);
    my_server()->info.fds[0].fd = my_server()->info.server_fd;
    my_server()->info.fds[0].events = POLLIN;
    my_server()->info.fd_count = 1;
    server_loop();
    for (int i = 0; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.fds[i].fd >= 0) {
            close(my_server()->info.fds[i].fd);
        }
    }
    return EXIT_SUCCESS;
}
