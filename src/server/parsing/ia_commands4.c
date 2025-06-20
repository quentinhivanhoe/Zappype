/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands4
*/

#include "../includes/server.h"
#include "../includes/ia.h"

void handle_incantation(trn_t *trantorian, char **args)
{
    static const uint8_t elevation_tab[7][7] = {
        {1, 1, 0, 0, 0, 0, 0},
        {2, 1, 1, 1, 0, 0, 0},
        {2, 2, 0, 1, 0, 2, 0},
        {4, 1, 1, 2, 0, 1, 0},
        {4, 1, 2, 1, 3, 0, 0},
        {6, 1, 2, 3, 0, 1, 0},
        {6, 2, 2, 2, 2, 2, 1}
    };

    int lvl = trantorian->lvl;
    if (lvl < 1 || lvl > 7) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;
    tile_t *tile = &my_server()->map[y * width + x];
    const uint8_t *req = elevation_tab[lvl - 1];

    for (int i = 0; i < OBJECT_DEFINED; i++) {
        if (tile->content[i] < req[i]) {
            dprintf(trantorian->socket, "ko\n");
            return;
        }
    }
    int player_count = 0;
    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        trn_t *other = &my_server()->info.clients[i].data.ia_client;
        if (other->pos.x == x && other->pos.y == y && other->lvl == lvl)
            player_count++;
    }
    if (player_count < req[0]) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    for (int i = 0; i < OBJECT_DEFINED; i++) {
        tile->content[i] -= req[i];
    }
    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        trn_t *other = &my_server()->info.clients[i].data.ia_client;
        if (other->pos.x == x && other->pos.y == y && other->lvl == lvl) {
            other->lvl++;
            dprintf(other->socket, "Current level: %d\n", other->lvl);
        }
    }
    dprintf(trantorian->socket, "Elevation underway\n");
    (void)args;
}
