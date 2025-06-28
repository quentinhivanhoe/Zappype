/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** edi_command
*/

#include "../includes/server.h"

void edi_command(size_t egg_id)
{
    for (size_t i = 1; i <= my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd <= 0 ||
            my_server()->info.clients[i].type != GUI)
            continue;
        dprintf(my_server()->info.fds[i].fd,
            "edi #%zu\n", egg_id);
    }
}
