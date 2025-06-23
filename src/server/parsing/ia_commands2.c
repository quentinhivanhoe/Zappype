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
    team_t team = my_server()->params.teams[trantorian->team_id];

    dprintf(trantorian->socket, "%lu\n", team.egg_count);
    if (my_server()->params.debug_mode) {
        dprintf(STDERR_FILENO, "Team: %s\n", team.name);
        dprintf(STDERR_FILENO, "\tegg: %ld\n", team.egg_count);
        dprintf(STDERR_FILENO, "\ttrantorian: %ld\n", team.trn_count);
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

static int get_object_index(const char *name)
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
