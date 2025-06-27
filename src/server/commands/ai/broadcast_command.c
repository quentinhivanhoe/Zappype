/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** broadcast_command
*/
#include "../includes/server.h"
#include "../includes/ia.h"
#include <math.h>

const int mapping[4][8] = {
    {2, 1, 8, 7, 6, 5, 4, 3},
    {4, 3, 2, 1, 8, 7, 6, 5},
    {6, 5, 4, 3, 2, 1, 8, 7},
    {8, 7, 6, 5, 4, 3, 2, 1}
};

static int compute_broadcast_direction(trn_t *sender, size_t i)
{
    trn_t *receiver = &my_server()->info.clients[i].data.ia_client;
    int dx = receiver->pos.x - sender->pos.x;
    int dy = receiver->pos.y - sender->pos.y;
    double angle_rad = atan2(dy, dx);
    double angle_deg = angle_rad * (180.0 / M_PI);
    int sector = 0;
    int dir_index = 0;

    if (angle_deg < 0)
        angle_deg += 360.0;
    sector = (int)((angle_deg + 22.5) / 45.0);
    if (sector == 8)
        sector = 0;
    dir_index = receiver->pos.dir - 1;
    return mapping[dir_index][sector];
}

static size_t get_trantorian_index(trn_t *trantorian)
{
    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd == -1)
            continue;
        if (my_server()->info.clients[i].type == IA &&
            &my_server()->info.clients[i].data.ia_client == trantorian) {
            return i;
        }
    }
    return 0;
}

void handle_broadcast(trn_t *trantorian, char **args)
{
    if (!args || !args[1]) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd == -1
        || i == get_trantorian_index(trantorian))
            continue;
        if (my_server()->info.clients[i].type == GUI)
            dprintf(my_server()->info.clients[i].data.gui_client,
            "pbc #%zu %s\n", get_trantorian_index(trantorian), args[1]);
        if (my_server()->info.clients[i].type == IA) {
            dprintf(my_server()->info.clients[i].data.ia_client.socket,
            "message %d,%s\n", compute_broadcast_direction(trantorian, i),
            args[1]);
        }
    }
    dprintf(trantorian->socket, "ok\n");
}
