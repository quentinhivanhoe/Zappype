/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** right_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Handles the "Right" command from a trantorian.
 *
 * Rotates the trantorian 90 degrees to the right (counter-clockwise).
 * Directions follow a clockwise convention:
 * - 1 = NORTH
 * - 2 = EAST
 * - 3 = SOUTH
 * - 4 = WEST
 *
 * @param trantorian Pointer to the trantorian structure.
 * @param args Unused command arguments.
 */

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
