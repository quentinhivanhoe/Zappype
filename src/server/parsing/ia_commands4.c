/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands4
*/

#include "../includes/server.h"
#include "../includes/ia.h"

static const uint8_t elevation_tab[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

static bool check_resources(tile_t *tile, const uint8_t *req)
{
    for (int i = 1; i < 7; i++) {
        if (tile->content[i] < req[i])
            return false;
    }
    return true;
}

static int count_trantorians_same_level(int lvl)
{
    int count = 0;
    trn_t *other = NULL;

    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        other = &my_server()->info.clients[i].data.ia_client;
        if (other->lvl == lvl)
            count++;
    }
    return count;
}

static void consume_resources(tile_t *tile, const uint8_t *req)
{
    for (int i = 1; i < 7; i++)
        tile->content[i] -= req[i];
}

void handle_incantation(trn_t *trantorian, char **args)
{
    int lvl = trantorian->lvl;
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;
    tile_t *tile = &my_server()->map[y * width + x];
    const uint8_t *req;

    if (lvl < 1 || lvl > 7) {
        dprintf(trantorian->socket, "ko1\n");
        return;
    }
    req = elevation_tab[lvl - 1];
    if (!check_resources(tile, req) || count_trantorians_same_level(lvl) < req[0]) {
        dprintf(trantorian->socket, "ko2\n");
        return;
    }
    dprintf(trantorian->socket, "Elevation underway\n");
    if (!check_resources(tile, req) || count_trantorians_same_level(lvl) < req[0]) {
        dprintf(trantorian->socket, "ko3\n");
        return;
    }
    consume_resources(tile, req);
    trantorian->lvl++;
    dprintf(trantorian->socket, "Current level: %d\n", trantorian->lvl);
    if (my_server()->params.debug_mode) {
        dprintf(2, "**********Incantation complète : (%lu, %lu) -> level %d**********\n",
                x, y, trantorian->lvl);
    }
    (void)args;
}
