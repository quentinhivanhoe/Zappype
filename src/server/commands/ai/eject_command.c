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

void kill_egg(size_t egg_id)
{
    trn_t *egg = &my_server()->info.clients[egg_id].data.ia_client;

    memset(egg, 0, sizeof(trn_t));
    my_server()->info.fds[egg_id].fd = -1;
    my_server()->info.fd_count--;
    edi_command(egg_id);
}

void process_eject(trn_t *trantorian, size_t id)
{
    trn_t *other = &my_server()->info.clients[id].data.ia_client;

    if (my_server()->info.clients[id].type == EGG) {
        kill_egg(id);
        return;
    }
    move_player(other, trantorian->pos.dir, my_server()->params.width,
    my_server()->params.height);
    send_eject(other, trantorian->pos.dir);
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
    trn_t *other = NULL;

    for (size_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.clients[i].type != IA
        && my_server()->info.clients[i].type != EGG)
            continue;
        other = &my_server()->info.clients[i].data.ia_client;
        if (other == trantorian)
            continue;
        if (other->pos.x == x && other->pos.y == y) {
            process_eject(trantorian, i);
            has_ejected = true;
        }
    }
    dprintf(trantorian->socket, has_ejected ? "ok\n" : "ko\n");
}
