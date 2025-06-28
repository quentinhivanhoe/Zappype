/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** inventory_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Handle the `Inventory` command for a trantorian.
 *
 * Sends the content of the trantorian's inventory in the following format:
 * [food X, linemate X, deraumere X, sibur X, mendiane X, phiras X, thystame X]
 *
 * @param trantorian Pointer to the trantorian.
 * @param args Unused command arguments.
 */
void handle_inventory(trn_t *trantorian, char **args)
{
    dprintf(trantorian->socket,
        "[food %lu, linemate %lu, deraumere %lu, sibur %lu,",
        trantorian->inventory[FOOD],
        trantorian->inventory[LINEMATE],
        trantorian->inventory[DERAUMERE],
        trantorian->inventory[SIBUR]);
    dprintf(trantorian->socket,
        " mendiane %lu, phiras %lu, thystame %lu]\n",
        trantorian->inventory[MENDIANE],
        trantorian->inventory[PHIRAS],
        trantorian->inventory[THYSTAME]);
    if (my_server()->params.debug_mode) {
        dprintf(2, "Inventory sent for client on socket %d\n",
            trantorian->socket);
    }
    (void)args;
}
