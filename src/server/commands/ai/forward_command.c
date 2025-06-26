/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** forward_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Computes the new coordinates based on the trantorian's direction.
 *
 * This function updates the given coordinates pointer based on the direction
 * of the trantorian, applying map wrapping if necessary.
 *
 * @param trantorian Pointer to the trantorian structure.
 * @param x Pointer to the X coordinate to update.
 * @param y Pointer to the Y coordinate to update.
 * @return true if direction is valid and update is successful, false otherwise
 */

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

/**
 * @brief Computes and applies the trantorian's forward movement.
 *
 * This function calculates the new position of the trantorian one tile ahead
 * in the direction it's currently facing. It also sends a position update
 * (ppo) to any connected GUI clients.
 *
 * @param trn Pointer to the trantorian structure.
 * @return true if the move was successful, false otherwise.
 */
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

/**
 * @brief Handles the "Forward" command from a trantorian.
 *
 * This function moves the trantorian one tile forward based on its direction,
 * wrapping around the map edges if necessary. If successful, it replies "ok"
 * to the client. If direction is invalid, it sends an error.
 *
 * @param trantorian Pointer to the trantorian structure.
 * @param args Unused command arguments.
 */
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
