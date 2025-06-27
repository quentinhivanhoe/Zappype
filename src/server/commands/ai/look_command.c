/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** look_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Get the object name as a string from its index.
 *
 * @param idx Index of the object (e.g., FOOD, LINEMATE, etc.)
 * @return const char* The string name of the object.
 */
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

/**
 * @brief Print all players (except the sender) on the specified tile.
 *
 * @param fd File descriptor of the client receiving the output.
 * @param x X coordinate of the tile.
 * @param y Y coordinate of the tile.
 * @param first Pointer to a bool indicating if it's the first printed item.
 */
static void print_tile_players(int fd, uint64_t x, uint64_t y, bool *first)
{
    trn_t *other = 0;

    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        other = &my_server()->info.clients[i].data.ia_client;
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

/**
 * @brief Print a given object multiple times if it exists on a tile.
 *
 * @param n Number of objects to print.
 * @param i Object index.
 * @param fd File descriptor to print to.
 * @param first True if it's the first printed item in the list.
 * @return bool Updated value of the `first` flag.
 */
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

/**
 * @brief Print the full content of a tile (resources and players).
 *
 * @param fd File descriptor of the client receiving the output.
 * @param tile Pointer to the tile.
 * @param x X coordinate of the tile.
 * @param y Y coordinate of the tile.
 */
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

/**
 * @brief Compute the starting coordinates for a row of vision tiles.
 *
 * @param trn Pointer to the trantorian.
 * @param lvl Vision level (distance from the player).
 * @param x Pointer to store the starting X coordinate.
 * @param y Pointer to store the starting Y coordinate.
 */
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

/**
 * @brief Compute coordinates of a tile in the row based on the player's
 *          direction.
 *
 * @param trn Pointer to the trantorian.
 * @param til Total number of tiles in the row.
 * @param i Index of the tile in the row.
 * @param pos Pointer to the (x, y) position array.
 */
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

/**
 * @brief Print all tiles in a specific row of vision.
 *
 * @param trantorian Pointer to the trantorian.
 * @param lvl Vision level (distance from the player).
 * @param tiles Number of tiles in the row.
 * @param first Pointer to a bool indicating if it's the first printed item.
 */
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

/**
 * @brief Handle the `Look` command for a trantorian.
 *
 * Outputs the content of the surrounding tiles depending on the player's level
 *
 * @param trantorian Pointer to the trantorian.
 * @param args Unused command arguments.
 */
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
