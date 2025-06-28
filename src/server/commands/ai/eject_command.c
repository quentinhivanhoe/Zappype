/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** eject_command
*/

#include "../includes/server.h"
#include "../includes/ia.h"

/**
 * @brief Moves a trantorian one tile forward based on a given direction.
 *
 * The movement is performed on a toroidal (wrapped) map. If the trantorian
 * moves out of bounds, it wraps around to the opposite side.
 *
 * @param trantorian Pointer to the trantorian to move.
 * @param dir The direction in which to move (NORTH, SOUTH, EAST, WEST).
 * @param width The width of the map.
 * @param height The height of the map.
 */
void move_player(trn_t *trantorian, int dir, int width, int height)
{
    if (dir == NORTH)
        trantorian->pos.y = (trantorian->pos.y + height - 1) % height;
    if (dir == SOUTH)
        trantorian->pos.y = (trantorian->pos.y + 1) % height;
    if (dir == EAST)
        trantorian->pos.x = (trantorian->pos.x + 1) % width;
    if (dir == WEST)
        trantorian->pos.x = (trantorian->pos.x + width - 1) % width;
}

static void send_eject(trn_t *trantorian, int dir)
{
    dprintf(trantorian->socket, "eject: %d\n", dir);
    send_pex(trantorian);
}

/**
 * @brief Handles the `Eject` command for a trantorian.
 *
 * Ejects all other trantorians located on the same tile as the current
 * trantorian. Each affected player is moved one tile in the direction
 * of the ejecting player and receives an `eject: <dir>` message.
 *
 * If at least one player was ejected, the current trantorian receives `ok`,
 * otherwise `ko` is sent.
 *
 * @param trantorian Pointer to the trantorian issuing the command.
 * @param args Unused command arguments.
 */
void handle_eject(trn_t *trantorian, __attribute_maybe_unused__ char **args)
{
    bool has_ejected = false;
    uint64_t x = trantorian->pos.x;
    uint64_t y = trantorian->pos.y;
    int width = my_server()->params.width;
    int height = my_server()->params.height;
    trn_t *other = NULL;

    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA)
            continue;
        other = &my_server()->info.clients[i].data.ia_client;
        if (other == trantorian)
            continue;
        if (other->pos.x == x && other->pos.y == y) {
            move_player(other, trantorian->pos.dir, width, height);
            send_eject(other, trantorian->pos.dir);
            has_ejected = true;
        }
    }
    dprintf(trantorian->socket, has_ejected ? "ok\n" : "ko\n");
}
