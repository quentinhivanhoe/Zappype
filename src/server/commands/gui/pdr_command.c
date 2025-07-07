/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pdr_command
*/
#include "../../includes/server.h"
#include "../../includes/gui.h"

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

static void print_tile(pos_t pos, int gui_id)
{
    tile_t tile = get_object(my_server()->map, pos.x, pos.y);

    dprintf(gui_id, "bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", pos.x, pos.y,
        tile.content[FOOD], tile.content[LINEMATE], tile.content[DERAUMERE],
        tile.content[SIBUR], tile.content[MENDIANE], tile.content[PHIRAS],
        tile.content[THYSTAME]);
}

static void print_inv(int trn_id, int gui_id)
{
    client_t *client = get_client(trn_id);
    trn_t trn = {0};

    if (!client) {
        fprintf(stderr, "NULL\n");
        return;
    }
    if (client->type == IA)
        trn = client->data.ia_client;
    dprintf(gui_id, "pin #%d %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        trn_id, trn.pos.x, trn.pos.y, trn.inventory[FOOD],
        trn.inventory[LINEMATE], trn.inventory[DERAUMERE],
        trn.inventory[SIBUR], trn.inventory[MENDIANE], trn.inventory[PHIRAS],
        trn.inventory[THYSTAME]);
    print_tile(trn.pos, gui_id);
}

void pdr_command(int player_id, obj_idx_t object)
{
    const char *obj_name = get_object_name(object);
    size_t id = 0;

    for (size_t i = 0; i < my_server()->params.max_clients; i++)
        if (my_server()->info.fds[i].fd == player_id)
            id = i;
    for (int fd = get_gui(); fd > 0; fd = get_gui()) {
        dprintf(fd, "pdr #%ld %s\n", id, obj_name);
        print_inv(id, fd);
    }
}

void pgt_command(int player_id, obj_idx_t object)
{
    const char *obj_name = get_object_name(object);
    size_t id = 0;

    for (size_t i = 0; i < my_server()->params.max_clients; i++)
        if (my_server()->info.fds[i].fd == player_id)
            id = i;
    for (int fd = get_gui(); fd > 0; fd = get_gui()) {
        dprintf(fd, "pgt #%ld %s\n", id, obj_name);
        print_inv(id, fd);
    }
}
