/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands
*/

#include "../includes/server.h"
#include "../includes/ia.h"

static bool compute_new_coords(trn_t *trantorian, uint64_t *x, uint64_t *y)
{
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;

    switch (trantorian->pos.dir) {
        case NORTH:
            *y = (*y == 0) ? height - 1 : *y - 1;
            break;
        case SOUTH:
            *y = (*y + 1) % height;
            break;
        case EAST:
            *x = (*x + 1) % width;
            break;
        case WEST:
            *x = (*x == 0) ? width - 1 : *x - 1;
            break;
        default:
            return false;
    }
    return true;
}

static bool compute_forward_position(trn_t *trn)
{
    uint64_t new_x = trn->pos.x;
    uint64_t new_y = trn->pos.y;
    int id = 0;

    if (!compute_new_coords(trn, &new_x, &new_y))
        return false;
    for (; (size_t)id < my_server()->params.max_clients; id++) {
        if (my_server()->info.clients[id].type != IA)
            continue;
        if (my_server()->info.clients[id].data.ia_client.socket == trn->socket)
            break;
    }
    for (int fd = get_gui(); fd > 0; fd = get_gui())
        dprintf(fd, "ppo #%d %ld %ld %d\n", id, new_x, new_y, trn->pos.dir);
    trn->pos.x = new_x;
    trn->pos.y = new_y;
    return true;
}

void handle_forward(trn_t *trantorian, __attribute_maybe_unused__ char **args)
{
    if (!compute_forward_position(trantorian)) {
        dprintf(trantorian->socket, "Direction isn't set yet !\n");
        return;
    }
    dprintf(trantorian->socket, "ok\n");
    if (my_server()->params.debug_mode) {
        dprintf(2, "Forward: new position = (%lu, %lu) direction %d\n",
                trantorian->pos.x, trantorian->pos.y, trantorian->pos.dir);
    }
}

void handle_right(trn_t *trantorian, char **args)
{
    int test;

    if (trantorian->pos.dir == 1)
        test = 2;
    if (trantorian->pos.dir == 2)
        test = 3;
    if (trantorian->pos.dir == 3)
        test = 4;
    if (trantorian->pos.dir == 4)
        test = 1;
    dprintf(trantorian->socket, "ok\n");
    if (my_server()->params.debug_mode) {
        printf("Right: Old direction: %d new direction %d\n",
            trantorian->pos.dir, test);
    }
    trantorian->pos.dir = test;
    (void)args;
}

void handle_left(trn_t *trantorian, char **args)
{
    int test;

    if (trantorian->pos.dir == 1)
        test = 4;
    if (trantorian->pos.dir == 4)
        test = 3;
    if (trantorian->pos.dir == 3)
        test = 2;
    if (trantorian->pos.dir == 2)
        test = 1;
    dprintf(trantorian->socket, "ok\n");
    if (my_server()->params.debug_mode) {
        printf("Left: Old direction: %d new direction %d\n",
            trantorian->pos.dir, test);
    }
    trantorian->pos.dir = test;
    (void)args;
}
