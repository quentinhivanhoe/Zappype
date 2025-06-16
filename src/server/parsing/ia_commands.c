/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia_commands
*/

#include "../includes/server.h"
#include "../includes/ia.h"

void handle_forward(__attribute_maybe_unused__ trn_t *trantorian,__attribute_maybe_unused__ char **args)
{
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    uint64_t width = my_server()->params.width;
    uint64_t height = my_server()->params.height;

    printf("gros caca de pipi de poulet de sauce d'huitre\n");
    switch (trantorian->pos.dir) {
        case NORTH:
            y = (y == 0) ? height - 1 : y - 1;
            break;
        case SOUTH:
            y = (y + 1) % height;
            break;
        case EAST:
            x = (x + 1) % width;
            break;
        case WEST:
            x = (x == 0) ? width - 1 : x - 1;
            break;
        default:
            dprintf(trantorian->socket, "ko\n");
            return;
    }
    trantorian->pos.x = x;
    trantorian->pos.y = y;
    dprintf(trantorian->socket, "ok\n");
    if (my_server()->params.debug_mode) {
        dprintf(2, "Forward: new position = (%lu, %lu)\n", x, y);
    }
}