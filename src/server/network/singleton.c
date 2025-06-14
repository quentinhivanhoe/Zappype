/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** singleton
*/

#include "../includes/server.h"

server_t *my_server(void)
{
    static server_t server;

    return &server;
}

client_t *get_client(size_t client_idx)
{
    if (client_idx == 0 || client_idx >= my_server()->info.fd_count
    || my_server()->info.fds[client_idx].fd == -1) {
        return NULL;
    }
    return &my_server()->info.clients[client_idx];
}
