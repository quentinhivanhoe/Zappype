/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** write_gui
*/
#include "../../includes/server.h"
#include <stdarg.h>

int get_gui(void)
{
    static size_t id = 0;
    client_t *clients = my_server()->info.clients;

    for (; clients; clients = clients->next) {
        if (clients->id <= id) {
            id++;
            continue;
        }
    }
    if (!clients)
        return -1;
    for (; clients; clients = clients->next) {
        if (clients->type != GUI)
            continue;
        if (clients->data.gui_client == -1)
            continue;
        return clients->data.gui_client;
    }
    id = 0;
    return -1;
}
