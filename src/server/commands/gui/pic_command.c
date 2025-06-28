/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pic_command
*/

#include "../../includes/server.h"

void send_pic(trn_t *trn, char *token)
{
    if (!trn || !token || !token[0])
        return;
    if (strcmp(token, "Incantation") != 0)
        return;
    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd <= 0)
            continue;
        if (my_server()->info.clients[i].type == GUI) {
            dprintf(my_server()->info.clients[i].data.gui_client,
            "pic %zu %zu %d #%ld\n", trn->pos.x, trn->pos.y, trn->lvl,
            get_trantorian_index(trn));
        }
    }
}

void send_pie(trn_t *trantorian, bool state)
{
    if (!trantorian)
        return;
    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd <= 0)
            continue;
        if (my_server()->info.clients[i].type == GUI) {
            dprintf(my_server()->info.clients[i].data.gui_client,
            "pie %zu %zu %c\n", trantorian->pos.x, trantorian->pos.y,
            state ? 'T' : 'F');
        }
    }
}
