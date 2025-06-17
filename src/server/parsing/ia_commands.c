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

static bool compute_forward_position(trn_t *trantorian)
{
    uint64_t new_x = trantorian->pos.x;
    uint64_t new_y = trantorian->pos.y;

    if (!compute_new_coords(trantorian, &new_x, &new_y))
        return false;
    trantorian->pos.x = new_x;
    trantorian->pos.y = new_y;
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
