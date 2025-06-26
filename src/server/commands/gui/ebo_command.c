/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ebo_command
*/
#include "../../includes/server.h"

void ebo_command(size_t id)
{
    client_t *client = get_client_by_id(id);
    int fd = 0;

    if (!client)
        return;
    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next) {
        if (cli->type == GUI && cli->data.gui_client > 0) {
            fd = cli->data.gui_client;
            dprintf(fd, "ebo #%ld\n", id);
            pnw_command(client->data.ia_client, id, fd);
        }
    }
}
