/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** set_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Executes the logic for the `Set` command.
 *
 * This function allows a trantorian to drop one unit of a specific object
 * from their inventory onto the current tile. If the object is not available
 * in the inventory, the command fails.
 *
 * @param trantorian Pointer to the trantorian issuing the command.
 * @param obj_idx Index of the object to drop (must be valid).
 */
static void execute_set(trn_t *trantorian, int obj_idx)
{
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;
    tile_t *tile = &my_server()->map[y * width + x];

    if (trantorian->inventory[obj_idx] == 0) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    trantorian->inventory[obj_idx]--;
    tile->content[obj_idx]++;
    pdr_command(trantorian->socket, obj_idx);
    dprintf(trantorian->socket, "ok\n");
}

/**
 * @brief Handles the `Set` command issued by a trantorian.
 *
 * Parses the command arguments to identify the object to drop,
 * validates the object name, and calls the function to execute the drop.
 *
 * Sends "ok" on success or "ko" on failure.
 *
 * @param trantorian Pointer to the trantorian issuing the command.
 * @param args Array of strings where args[1] is expected to be the object name
 */
void handle_set(trn_t *trantorian, char **args)
{
    int obj_idx;

    if (!args || !args[0]) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    obj_idx = get_object_index(args[1]);
    if (obj_idx < 0) {
        dprintf(trantorian->socket, "ko\n");
        return;
    }
    execute_set(trantorian, obj_idx);
}
