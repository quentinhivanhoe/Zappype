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

static bool can_incantate(trn_t *trantorian, const uint8_t *req, tile_t *tile)
{
    if (!check_resources(tile, req))
        return false;
    if (count_trantorians_same_level(trantorian->lvl) < req[0])
        return false;
    return true;
}

void complete_incantation(trn_t *trantorian, const uint8_t *req, tile_t *tile)
{
    consume_resources(tile, req);
    trantorian->lvl++;
    dprintf(trantorian->socket, "Current level: %d\n", trantorian->lvl);
    if (my_server()->params.debug_mode) {
        dprintf(2, "Incantation complete : (%lu, %lu) -> level %d\n",
                trantorian->pos.x, trantorian->pos.y, trantorian->lvl);
    }
}

static bool is_valid_level(int lvl)
{
    return lvl >= 1 && lvl <= 7;
}

static tile_t *get_trantorian_tile(trn_t *trantorian)
{
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;

    return &my_server()->map[y * width + x];
}

void handle_incantation(trn_t *trantorian, char **args)
{
    const uint8_t *req;
    tile_t *tile;

    if (!is_valid_level(trantorian->lvl)) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    req = elevation_tab[trantorian->lvl - 1];
    tile = get_trantorian_tile(trantorian);
    if (!can_incantate(trantorian, req, tile)) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    dprintf(trantorian->socket, "Elevation underway\n");
    if (!can_incantate(trantorian, req, tile)) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    complete_incantation(trantorian, req, tile);
    (void)args;
}
