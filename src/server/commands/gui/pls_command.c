/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pls_command
*/
#include "../../includes/server.h"

void pls_command(int client_fd, __attribute_maybe_unused__ char **cmd)
{
    trn_t trn = {0};

    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next) {
        if (cli->type != IA)
            continue;
        if (cli->data.ia_client.socket < 0)
            continue;
        trn = cli->data.ia_client;
        dprintf(client_fd, "pls #%ld %ld %ld %d %d %s %d\n",
            cli->id, trn.pos.x, trn.pos.y, trn.pos.dir, trn.stat,
            my_server()->params.teams[trn.team_id].name, trn.lvl);
    }
}
