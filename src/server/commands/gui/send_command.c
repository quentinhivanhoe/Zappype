/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** send_command
*/

#include "../includes/server.h"

void send_pex(trn_t *trantorian)
{
    if (!trantorian)
        return;
    for (size_t i = 1; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd <= 0
        || my_server()->info.clients[i].type != GUI)
            continue;
        dprintf(my_server()->info.fds[i].fd, "pex #%ld\n",
        get_trantorian_index(trantorian));
    }
}
