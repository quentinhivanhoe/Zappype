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
    static size_t i = 0;
    client_t *clients = my_server()->info.clients;

    for (; i < my_server()->params.max_clients; i++) {
        if (clients[i].type != GUI)
            continue;
        if (clients[i].data.gui_client == -1)
            continue;
        i++;
        return clients[i - 1].data.gui_client;
    }
    i = 0;
    return -1;
}
