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

static void print_tile_players(int fd, uint64_t x, uint64_t y, bool *first)
{
    trn_t *other = 0;

    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next) {
        if (cli->type != IA)
            continue;
        other = &cli->data.ia_client;
        if (other->socket == fd)
            continue;
        if (other->pos.x != x || other->pos.y != y)
            continue;
        if (!*first)
            dprintf(fd, " ");
        dprintf(fd, "player");
        *first = false;
    }
}

static bool print_object(uint64_t n, int i, int fd, bool first)
{
    while (n > 0) {
        if (!first)
            dprintf(fd, " ");
        dprintf(fd, "%s", get_object_name(i));
        first = false;
        n--;
    }
    return first;
}

static void print_tile_content(int fd, tile_t *tile, uint64_t x, uint64_t y)
{
    bool first = true;
    int64_t n = 0;

    for (int i = 0; i < OBJECT_DEFINED; i++)
        dprintf(2, " %s=%lu", get_object_name(i), tile->content[i]);
    dprintf(2, "\n");
    for (int i = 0; i < OBJECT_DEFINED; i++) {
        n = tile->content[i];
        first = print_object(n, i, fd, first);
    }
    print_tile_players(fd, x, y, &first);
}

static void compute_row_base(trn_t *trn, uint8_t lvl, int64_t *x, int64_t *y)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;

    *x = trn->pos.x;
    *y = trn->pos.y;
    switch (trn->pos.dir) {
        case NORTH:
            *y = (*y - lvl + height) % height;
            break;
        case SOUTH:
            *y = (*y + lvl) % height;
            break;
        case EAST:
            *x = (*x + lvl) % width;
            break;
        case WEST:
            *x = (*x - lvl + width) % width;
            break;
    }
}

static void compute_tile_coords(trn_t *trn, size_t til, size_t i, int64_t *pos)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;

    switch (trn->pos.dir) {
        case NORTH:
            pos[0] = (pos[0] - (til / 2) + i + width) % width;
            break;
        case SOUTH:
            pos[0] = (pos[0] + (til / 2) - i + width) % width;
            break;
        case EAST:
            pos[1] = (pos[1] - (til / 2) + i + height) % height;
            break;
        case WEST:
            pos[1] = (pos[1] + (til / 2) - i + height) % height;
            break;
    }
}

static void look_row(trn_t *trantorian, uint8_t lvl, size_t tiles, bool *first)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;
    int64_t pos[2] = {0};

    compute_row_base(trantorian, lvl, &pos[0], &pos[1]);
    for (size_t i = 0; i < tiles; i++) {
        compute_tile_coords(trantorian, tiles, i, pos);
        if (!*first)
            dprintf(trantorian->socket, ", ");
        *first = false;
        print_tile_content(trantorian->socket,
            &my_server()->map[pos[1] * width + pos[0]], pos[0], pos[1]);
    }
    (void)height;
}

void handle_look(trn_t *trantorian, char **args)
{
    bool first = true;
    size_t nb_tiles;

    dprintf(trantorian->socket, "[");
    for (uint8_t lvl = 0; lvl <= trantorian->lvl; lvl++) {
        fprintf(stderr, "toto\n");
        nb_tiles = 1 + 2 * lvl;
        look_row(trantorian, lvl, nb_tiles, &first);
    }
    dprintf(trantorian->socket, "]\n");
    if (my_server()->params.debug_mode) {
        dprintf(2, "Look sent for client on socket %d\n", trantorian->socket);
    }
    (void)args;
}
