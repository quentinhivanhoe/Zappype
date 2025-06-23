/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ebo_command
*/
#include "../../includes/server.h"

void ebo_command(size_t id)
{
    for (int fd = get_gui(); fd > 0; fd = get_gui())
        dprintf(fd, "ebo #%ld\n", id);
    pnw_command(my_server()->info.clients[id].data.ia_client, id);
}
