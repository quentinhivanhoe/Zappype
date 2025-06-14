/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** gui_commands2
*/

#include "../includes/server.h"

static size_t tab_len(char **tab)
{
    ssize_t len = 0;

    if (!tab)
        return 0;
    while (tab[len])
        len++;
    return len;
}

void handle_ppo(int client_fd, char **cmd)
{
    size_t len = tab_len(cmd);
    size_t client_idx = 0;

    if (len != 2 || cmd[1][0] != '#') {
        dprintf(client_fd, "sbp\n");
        return;
    }
    client_idx = atoi(cmd[1] + 1);
    if (client_idx == 0 || client_idx >= my_server()->info.fd_count
    || my_server()->info.fds[client_idx].fd == -1
    || my_server()->info.clients[client_idx].type != IA) {
        dprintf(client_fd, "sbp\n");
        return;
    }
    dprintf(client_fd, "ppo #%zu %ld %ld %d\n", client_idx,
        my_server()->info.clients[client_idx].data.ia_client.pos.x,
        my_server()->info.clients[client_idx].data.ia_client.pos.y,
        my_server()->info.clients[client_idx].data.ia_client.pos.dir);
}
