/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** incantation_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Elevation requirements table for levels 1 through 7.
 *
 * Each row represents the requirements for a level:
 * - Column 0: number of required players of same level.
 * - Columns 1-6: required quantities for resources in the order:
 *   linemate, deraumere, sibur, mendiane, phiras, thystame.
 */
static const uint8_t elevation_tab[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

/**
 * @brief Checks if the tile has the required resources for elevation.
 *
 * @param tile Pointer to the tile.
 * @param req Array of required quantities.
 * @return true if all resources are sufficient, false otherwise.
 */
static bool check_resources(tile_t *tile, const uint8_t *req)
{
    for (int i = 1; i < 7; i++) {
        if (tile->content[i] < req[i])
            return false;
    }
    return true;
}

/**
 * @brief Counts how many trantorians on the server are at the same level.
 *
 * @param lvl Level to compare.
 * @return Number of trantorians at the same level.
 */
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

/**
 * @brief Removes the required resources from the tile.
 *
 * @param tile Pointer to the tile.
 * @param req Array of quantities to remove.
 */
static void consume_resources(tile_t *tile, const uint8_t *req)
{
    for (int i = 1; i < 7; i++)
        tile->content[i] -= req[i];
}

/**
 * @brief Verifies whether an incantation can be started.
 *
 * Checks if the tile has enough resources and there are enough
 * trantorians at the same level on the server.
 *
 * @param trantorian Pointer to the trantorian.
 * @param req Resource requirements for the elevation.
 * @param tile Pointer to the tile where the incantation is attempted.
 * @return true if incantation can proceed, false otherwise.
 */
static bool can_incantate(trn_t *trantorian, const uint8_t *req, tile_t *tile)
{
    if (!check_resources(tile, req))
        return false;
    if (count_trantorians_same_level(trantorian->lvl) < req[0])
        return false;
    return true;
}

/**
 * @brief Completes an incantation by consuming resources and leveling up.
 *
 * @param trantorian Pointer to the trantorian performing the incantation.
 * @param req Requirements used for this level-up.
 * @param tile Pointer to the tile the trantorian is standing on.
 */
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

/**
 * @brief Checks whether the trantorian's level is valid for elevation.
 *
 * Valid levels are in range [1, 7].
 *
 * @param lvl Level to validate.
 * @return true if level is valid, false otherwise.
 */
static bool is_valid_level(int lvl)
{
    return lvl >= 1 && lvl <= 7;
}

/**
 * @brief Gets the tile on which the trantorian is currently located.
 *
 * @param trantorian Pointer to the trantorian.
 * @return Pointer to the tile.
 */
static tile_t *get_trantorian_tile(trn_t *trantorian)
{
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;

    return &my_server()->map[y * width + x];
}

/**
 * @brief Handles the `Incantation` command.
 *
 * This function validates the elevation conditions (number of trantorians
 * of the same level and resource availability) and, if successful, upgrades
 * the level of the player after a second validation step.
 *
 * Sends "Elevation underway" followed by "Current level: X" or "ko".
 *
 * @param trantorian Pointer to the trantorian performing the incantation.
 * @param args Command arguments (unused).
 */
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
