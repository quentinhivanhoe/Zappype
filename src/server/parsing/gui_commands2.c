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

static int check_player_info(int client_fd, char **cmd)
{
    size_t len = tab_len(cmd);
    size_t client_idx = 0;

    if (len != 2 || cmd[1][0] != '#') {
        dprintf(client_fd, "sbp\n");
        return false;
    }
    client_idx = atoi(cmd[1] + 1);
    if (client_idx == 0 || client_idx >= my_server()->info.fd_count
    || my_server()->info.fds[client_idx].fd == -1
    || my_server()->info.clients[client_idx].type != IA) {
        dprintf(client_fd, "sbp\n");
        return false;
    }
    return client_idx;
}

void handle_ppo(int client_fd, char **cmd)
{
    size_t client_idx = check_player_info(client_fd, cmd);

    if (client_idx == false) {
        return;
    }
    dprintf(client_fd, "ppo #%zu %ld %ld %d\n", client_idx,
        my_server()->info.clients[client_idx].data.ia_client.pos.x,
        my_server()->info.clients[client_idx].data.ia_client.pos.y,
        my_server()->info.clients[client_idx].data.ia_client.pos.dir);
}

void handle_plv(int client_fd, char **cmd)
{
    size_t client_idx = check_player_info(client_fd, cmd);

    if (client_idx == false) {
        return;
    }
    dprintf(client_fd, "plv #%zu %d\n", client_idx,
        my_server()->info.clients->data.ia_client.lvl);
}

void handle_pin(int client_fd, char **cmd)
{
    size_t client_idx = check_player_info(client_fd, cmd);

    if (client_idx == false) {
        return;
    }
    dprintf(client_fd, "pin #%zu %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        client_idx,
        get_client(client_idx)->data.ia_client.pos.x,
        get_client(client_idx)->data.ia_client.pos.y,
        get_client(client_idx)->data.ia_client.inventory[FOOD],
        get_client(client_idx)->data.ia_client.inventory[LINEMATE],
        get_client(client_idx)->data.ia_client.inventory[DERAUMERE],
        get_client(client_idx)->data.ia_client.inventory[SIBUR],
        get_client(client_idx)->data.ia_client.inventory[MENDIANE],
        get_client(client_idx)->data.ia_client.inventory[PHIRAS],
        get_client(client_idx)->data.ia_client.inventory[THYSTAME]
    );
}
