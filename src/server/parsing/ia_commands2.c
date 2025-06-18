/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands2
*/

#include "../includes/server.h"
#include "../includes/ia.h"

void handle_connect_nbr(trn_t *trantorian, char **args)
{
    size_t total_slots = my_server()->params.cli_per_team;
    size_t used_slots = count_ia_clients(trantorian->team_id);
    size_t remaining = 0;

    if (total_slots > used_slots)
        remaining = total_slots - used_slots;
    dprintf(trantorian->socket, "%lu\n", remaining);
    if (my_server()->params.debug_mode) {
        dprintf(2, "Connect_nbr: team_id=%lu, used=%lu, remaining=%lu\n",
                trantorian->team_id, used_slots, remaining);
    }
    (void)args;
}

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
