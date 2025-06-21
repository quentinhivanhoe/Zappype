/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pdr_command
*/
#include "../../includes/server.h"

const char *get_object_name(obj_idx_t object)
{
    switch (object) {
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
            return NULL;
    }
}

void pdr_command(int player_id, obj_idx_t object)
{
    const char *obj_name = get_object_name(object);

    for (int fd = get_gui(); fd > 0; fd = get_gui())
        dprintf(fd, "pdr #%d %s\n", player_id, obj_name);
}

void pgt_command(int player_id, obj_idx_t object)
{
    const char *obj_name = get_object_name(object);

    for (int fd = get_gui(); fd > 0; fd = get_gui())
        dprintf(fd, "pgt #%d %s\n", player_id, obj_name);
}
