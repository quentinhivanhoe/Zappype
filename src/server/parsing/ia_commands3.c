/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands3
*/
#include "../includes/server.h"
#include "../includes/ia.h"

static const char *get_object_name(int idx)
{
    switch (idx) {
        case FOOD:
            return "food";
        case LINEMATE:
            return "linemate";
        case DERAUMERE:
            return "deraumere";
        case SIBUR:
            return "sibur";
        case MENDIANE:
            return "mendiane";
        case PHIRAS:
            return "phiras";
        case THYSTAME:
            return "thystame";
        default:
            return "unknown";
    }
}

static void print_tile_players(int fd, uint64_t x, uint64_t y, bool *first, const trn_t *self)
{
    const trn_t *other;

    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        other = &my_server()->info.clients[i].data.ia_client;
        if (other == self)
            continue;
        if (other->pos.x != x || other->pos.y != y)
            continue;
        if (!*first)
            dprintf(fd, " ");
        dprintf(fd, "player");
        *first = false;
    }
}

static void print_tile_content(int fd, tile_t *tile, uint64_t x, uint64_t y, const trn_t *self)
{
    bool first = true;
    dprintf(2, "DEBUG (%lu,%lu):", x, y);
    for (int i = 0; i < OBJECT_DEFINED; i++) {
        dprintf(2, " %s=%lu", get_object_name(i), tile->content[i]);
    }
    dprintf(2, "\n");
    for (int i = 0; i < OBJECT_DEFINED; i++) {
        uint64_t n = tile->content[i];
        while (n > 0) {
            if (!first)
                dprintf(fd, " ");
            dprintf(fd, "%s", get_object_name(i));
            first = false;
            n--;
        }
    }
    print_tile_players(fd, x, y, &first, self);
}


static void compute_row_base(trn_t *trantorian, uint8_t distance, int64_t *base_x, int64_t *base_y)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;

    *base_x = trantorian->pos.x;
    *base_y = trantorian->pos.y;
    switch (trantorian->pos.dir) {
        case NORTH: *base_y = (*base_y - distance + height) % height; break;
        case SOUTH: *base_y = (*base_y + distance) % height; break;
        case EAST:  *base_x = (*base_x + distance) % width; break;
        case WEST:  *base_x = (*base_x - distance + width) % width; break;
    }
}

static void compute_tile_coords(trn_t *trantorian, int64_t base_x, int64_t base_y,
                                size_t nb_tiles, size_t i, int64_t *x, int64_t *y)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;

    *x = base_x;
    *y = base_y;
    switch (trantorian->pos.dir) {
        case NORTH:
            *x = (base_x - (nb_tiles / 2) + i + width) % width;
            break;
        case SOUTH:
            *x = (base_x + (nb_tiles / 2) - i + width) % width;
            break;
        case EAST:
            *y = (base_y - (nb_tiles / 2) + i + height) % height;
            break;
        case WEST:
            *y = (base_y + (nb_tiles / 2) - i + height) % height;
            break;
    }
}

static void look_row(trn_t *trantorian, uint8_t distance, size_t nb_tiles, bool *first)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;
    int64_t base_x;
    int64_t base_y;
    int64_t x;
    int64_t y;

    compute_row_base(trantorian, distance, &base_x, &base_y);
    for (size_t i = 0; i < nb_tiles; i++) {
        compute_tile_coords(trantorian, base_x, base_y, nb_tiles, i, &x, &y);
        if (!*first)
            dprintf(trantorian->socket, ", ");
        *first = false;
        print_tile_content(trantorian->socket, &my_server()->map[y * width + x], x, y, trantorian);
    }
    (void)height;
}

void handle_look(trn_t *trantorian, char **args)
{
    bool first = true;
    size_t nb_tiles;

    dprintf(trantorian->socket, "[");
    for (uint8_t lvl = 0; lvl <= trantorian->lvl; lvl++) {
        nb_tiles = 1 + 2 * lvl;
        look_row(trantorian, lvl, nb_tiles, &first);
    }
    dprintf(trantorian->socket, "]\n");
    if (my_server()->params.debug_mode) {
        dprintf(2, "Look sent for client on socket %d\n", trantorian->socket);
    }
    (void)args;
}