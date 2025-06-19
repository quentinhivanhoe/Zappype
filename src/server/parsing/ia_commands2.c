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

// static int get_object_index(trn_t *trantoran, const char *name)
// {
//     if (strcmp(name, "food") == 0) {
//         trantoran->inventory[FOOD]++;
//         return FOOD;
//     }
//     if (strcmp(name, "linemate") == 0) {
//         trantoran->inventory[LINEMATE]++;
//         return LINEMATE;
//     }
//     if (strcmp(name, "deraumere") == 0) {
//         trantoran->inventory[DERAUMERE]++;
//         return DERAUMERE;
//     }
//     if (strcmp(name, "sibur") == 0) {
//         trantoran->inventory[SIBUR]++;
//         return SIBUR;
//     }
//     if (strcmp(name, "mendiane") == 0) {
//         trantoran->inventory[MENDIANE]++;
//         return MENDIANE;
//     }
//     if (strcmp(name, "phiras") == 0) {
//         trantoran->inventory[PHIRAS]++;
//         return PHIRAS;
//     }
//     if (strcmp(name, "thystame") == 0) {
//         trantoran->inventory[THYSTAME]++;
//         return THYSTAME;
//     }
//     return -1;
// }

// void handle_take(trn_t *trantorian, char **args)
// {
//     int obj_idx = 0;
//     uint64_t x = trantorian->pos.x;
//     uint64_t y = trantorian->pos.y;
//     tile_t *tile = &my_server()->map[x * my_server()->params.width + x];

//     if (!args || !args[0]) {
//         dprintf(trantorian->socket, "ko1\n");
//         return;
//     }
//     obj_idx = get_object_index(trantorian ,args[1]);
//     printf("Pess lmk la i rode prend ça: %s\n", args[1]);
//     if (obj_idx < 0) {
//         dprintf(trantorian->socket, "ko2\n");
//         return;
//     }
//     if (tile->content[obj_idx] == 0) {
//         dprintf(trantorian->socket, "ko3\n");
//         return;
//     }
//     dprintf(trantorian->socket, "ok\n");
//     if (my_server()->params.debug_mode) {
//         dprintf(2, "Take: %s, pos=(%lu,%lu), remaining=%lu\n",
//                 args[0], x, y, tile->content[obj_idx]);
//     }
// }
