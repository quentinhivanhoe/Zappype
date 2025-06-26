/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** clean_server
*/

#include "../includes/server.h"
#include "../includes/clock.h"

void clean_server(void)
{
    void *ptr = NULL;

    for (nfds_t i = 0; i < my_server()->info.fd_count; i++)
        if (my_server()->info.fds[i].fd >= 0)
            close(my_server()->info.fds[i].fd);
    for (int i = 0; my_server()->params.teams[i].name; i++)
        free(my_server()->params.teams[i].name);
    while (my_server()->info.clients) {
        ptr = my_server()->info.clients;
        my_server()->info.clients = my_server()->info.clients;
        free(ptr);
    }
    free(my_server()->params.teams);
    free(my_server()->map);
    clock_list(NULL, DESTROY);
}
