/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pdi_command
*/
#include "../../includes/server.h"

void pdi_command(size_t id)
{
    int fd = 0;

    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next) {
        if (cli->type == GUI && cli->data.gui_client > 0) {
            fd = cli->data.gui_client;
            dprintf(fd, "pdi #%ld\n", id);
        }
    }
}
