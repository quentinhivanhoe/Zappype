/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** gui_commands2
*/

#include "../../includes/server.h"

static size_t tab_len(char **tab)
{
    ssize_t len = 0;

    if (!tab)
        return 0;
    while (tab[len])
        len++;
    return len;
}

static trn_t *check_player_info(int client_fd, char **cmd)
{
    size_t len = tab_len(cmd);
    size_t client_idx = 0;
    client_t *client = NULL;

    if (len != 2 || cmd[1][0] != '#') {
        dprintf(client_fd, "sbp\n");
        return NULL;
    }
    client_idx = atoi(cmd[1] + 1);
    client = get_client_by_id(client_idx);
    if (!client)
        return NULL;
    if (client_idx == 0 || client_idx >= my_server()->info.fd_count
    || my_server()->info.fds[client_idx].fd == -1
    || client->type != IA) {
        dprintf(client_fd, "sbp\n");
        return false;
    }
    return &client->data.ia_client;
}

void handle_ppo(int client_fd, char **cmd)
{
    trn_t *trn = check_player_info(client_fd, cmd);
    size_t id = 0;

    if (!trn)
        return;
    id = atol(cmd[1] + 1);
    dprintf(client_fd, "ppo #%zu %ld %ld %d\n",
        id, trn->pos.x, trn->pos.y, trn->pos.dir);
}

void handle_plv(int client_fd, char **cmd)
{
    trn_t *trn = check_player_info(client_fd, cmd);
    size_t id = 0;

    if (!trn)
        return;
    id = atol(cmd[1] + 1);
    dprintf(client_fd, "plv #%zu %d\n", id, trn->lvl);
}

void handle_pin(int client_fd, char **cmd)
{
    trn_t *trn = check_player_info(client_fd, cmd);
    size_t id = 0;

    if (!trn)
        return;
    id = atol(cmd[1] + 1);
    dprintf(client_fd, "pin #%zu %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        id, trn->pos.x, trn->pos.y, trn->inventory[FOOD],
        trn->inventory[LINEMATE], trn->inventory[DERAUMERE],
        trn->inventory[SIBUR], trn->inventory[MENDIANE],
        trn->inventory[PHIRAS], trn->inventory[THYSTAME]
    );
}

void handle_sgt(int client_fd, char **cmd)
{
    if (tab_len(cmd) != 1) {
        dprintf(client_fd, "sbp\n");
    } else {
        dprintf(client_fd, "sgt %ld\n", my_server()->params.frequency);
    }
}

void handle_sst(int client_fd, char **cmd)
{
    int new_frequency = 0;

    if (tab_len(cmd) != 2 || !is_num(cmd[1])) {
        dprintf(client_fd, "sbp\n");
        return;
    }
    new_frequency = atoi(cmd[1]);
    my_server()->params.frequency = new_frequency;
    dprintf(client_fd, "sst %d\n", new_frequency);
}
