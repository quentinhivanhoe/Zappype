/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** els_command
*/
#include "../../includes/server.h"

void els_command(int client_fd, __attribute_maybe_unused__ char **cmd)
{
    client_t *clients = my_server()->info.clients;
    pos_t pos = {0};
    char *t = NULL;

    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (clients[i].type != EGG)
            continue;
        pos = clients[i].data.ia_client.pos;
        t = my_server()->params.teams[clients[i].data.ia_client.team_id].name;
        dprintf(client_fd, "els #%ld %ld %ld %s\n", i, pos.x, pos.y, t);
    }
}
