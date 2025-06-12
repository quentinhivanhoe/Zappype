/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** clean_server
*/

#include "../includes/server.h"


void clean_server(void)
{
    for (nfds_t i = 0; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.fds[i].fd >= 0) {
            close(my_server()->info.fds[i].fd);
        }
    }
    for (int i = 0; my_server()->params.team_names[i] != NULL; i++) {
        free(my_server()->params.team_names[i]);
    }
    free(my_server()->params.team_names);
}
