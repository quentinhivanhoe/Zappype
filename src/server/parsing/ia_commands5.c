/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands5
*/

#include "../includes/server.h"
#include "../includes/ia.h"

void move_player(trn_t *trantorian, int dir, int width, int height)
{
    if (dir == NORTH)
        trantorian->pos.y = (trantorian->pos.y + height - 1) % height;
    if (dir == SOUTH)
        trantorian->pos.y = (trantorian->pos.y + 1) % height;
    if (dir == EAST)
        trantorian->pos.x = (trantorian->pos.x + 1) % width;
    if (dir == WEST)
        trantorian->pos.x = (trantorian->pos.x + width - 1) % width;
}

void handle_eject(trn_t *trantorian, __attribute_maybe_unused__ char **args)
{
    bool has_ejected = false;
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    int width = my_server()->params.width;
    int height = my_server()->params.height;
    trn_t *other = NULL;

    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        other = &my_server()->info.clients[i].data.ia_client;
        if (other == trantorian)
            continue;
        if (other->pos.x == x && other->pos.y == y) {
            move_player(other, trantorian->pos.dir, width, height);
            dprintf(other->socket, "eject: %d\n", trantorian->pos.dir);
            has_ejected = true;
        }
    }
    dprintf(trantorian->socket, has_ejected ? "ok\n" : "ko\n");
}
