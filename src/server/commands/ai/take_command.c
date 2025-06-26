/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** take_command
*/
#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Returns the internal index of an object based on its name.
 *
 * This function maps object names (like "food", "linemate", etc.)
 * to their corresponding internal enum/index value.
 *
 * @param name The name of the object as a string.
 * @return The index of the object, or -1 if the name is invalid.
 */
int get_object_index(const char *name)
{
    if (strcmp(name, "food") == 0)
        return FOOD;
    if (strcmp(name, "linemate") == 0)
        return LINEMATE;
    if (strcmp(name, "deraumere") == 0)
        return DERAUMERE;
    if (strcmp(name, "sibur") == 0)
        return SIBUR;
    if (strcmp(name, "mendiane") == 0)
        return MENDIANE;
    if (strcmp(name, "phiras") == 0)
        return PHIRAS;
    if (strcmp(name, "thystame") == 0)
        return THYSTAME;
    return -1;
}

/**
 * @brief Executes the logic of taking an object from the map.
 *
 * If the object is available on the current tile, it is removed from the tile
 * and added to the trantorian's inventory. The appropriate GUI notification
 * is sent, and "ok" or "ko" is returned to the client.
 *
 * @param trantorian The trantorian attempting to take the object.
 * @param obj_idx The index of the object to take.
 */
static void execute_take(trn_t *trantorian, int obj_idx)
{
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;
    tile_t *tile = &my_server()->map[y * width + x];

    if (tile->content[obj_idx] == 0) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    tile->content[obj_idx]--;
    trantorian->inventory[obj_idx]++;
    pgt_command(trantorian->socket, obj_idx);
    dprintf(trantorian->socket, "ok\n");
}

/**
 * @brief Handles the `Take` command issued by a trantorian.
 *
 * Validates the object name, retrieves its index, and executes the
 * take operation. Sends "ok" if successful, "ko" otherwise.
 *
 * @param trantorian The trantorian issuing the command.
 * @param args The command arguments (args[1] should be the object name).
 */
void handle_take(trn_t *trantorian, char **args)
{
    int obj_idx;

    if (!args || !args[1]) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    obj_idx = get_object_index(args[1]);
    if (obj_idx < 0) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    execute_take(trantorian, obj_idx);
}
