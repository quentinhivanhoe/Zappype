/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** main
*/

#include "./includes/server.h"

int main(int argc, char **argv)
{
    signal(SIGINT, signal_handler);
    memset(my_server(), 0, sizeof(server_t));
    my_server()->info.fd_count = 0;
    det_params(argc, argv);
    check_params();
    if (my_server()->params.debug_mode == true)
        print_params();
    my_server()->info.port = my_server()->params.port;
    if (setup_server() < 0)
        return EXIT_FAILURE;
    printf("Server listening on port %d...\n", my_server()->info.port);
    my_server()->info.fds[0].fd = my_server()->info.server_fd;
    my_server()->info.fds[0].events = POLLIN;
    my_server()->info.fd_count = 1;
    server_loop();
    clean_server();
    return EXIT_SUCCESS;
}
