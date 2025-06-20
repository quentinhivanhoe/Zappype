/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pls_command
*/
#include "../../includes/server.h"

void pls_command(int client_fd, __attribute_maybe_unused__ char **cmd)
{
    client_t *clients = my_server()->info.clients;
    trn_t trn = {0};

    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (clients[i].type != IA)
            continue;
        if (clients[i].data.ia_client.socket < 0)
            continue;
        trn = clients[i].data.ia_client;
        dprintf(client_fd, "pls #%d %ld %ld %d %d %s %d\n",
            trn.socket, trn.pos.x, trn.pos.y, trn.pos.dir, trn.stat,
            my_server()->params.team_names[trn.team_id], trn.lvl);
    }
}
