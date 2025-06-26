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
    char *team_name = NULL;
    size_t tid = 0;

    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next) {
        if (cli->type != EGG)
            continue;
        if (cli->data.ia_client.socket < 0)
            continue;
        pos = clients->data.ia_client.pos;
        tid = clients->data.ia_client.team_id;
        team_name = my_server()->params.teams[tid].name;
        dprintf(client_fd, "els #%ld %ld %ld %s\n",
                cli->id, pos.x, pos.y, team_name);
    }
}
