/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** fork_command
*/
#include "../../includes/ia.h"
#include "../../includes/server.h"

void enw_command(size_t egg_id, size_t trn_id, pos_t pos)
{
    for (int fd = get_gui(); fd != -1; fd = get_gui())
        dprintf(fd, "enw #%ld #%ld %ld %ld\n", egg_id, trn_id, pos.x, pos.y);
}

void handle_fork(trn_t *trn, __attribute_maybe_unused__ char **args)
{
    struct pollfd *fds = my_server()->info.fds;
    size_t idx = 0;
    size_t id = 0;

    for (; idx < my_server()->params.max_clients; idx++)
        if (fds[idx].fd == -1)
            break;
    for (; id < my_server()->params.max_clients; id++)
        if (fds[id].fd == trn->socket)
            break;
    if (idx == my_server()->params.max_clients
        || id == my_server()->params.max_clients) {
        dprintf(trn->socket, "ko\n");
        return;
    }
    my_server()->info.clients[idx].type = EGG;
    my_server()->info.clients[idx].data.ia_client = init_egg(trn->team_id);
    enw_command(idx, id, my_server()->info.clients[idx].data.ia_client.pos);
    my_server()->info.fds[idx].fd = 0;
    dprintf(trn->socket, "ok\n");
}
