/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** smg_command
*/

#include "../../includes/server.h"
#include <stdarg.h>

void smg_command(size_t client_id, const char *format, ...)
{
    va_list args;
    char buffer[BUFFER_SIZE];
    ssize_t len = 0;

    if (client_id >= my_server()->params.max_clients
    || my_server()->info.fds[client_id].fd <= 0
    || my_server()->info.clients[client_id].type != GUI)
        return;
    va_start(args, format);
    len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    if (len < 0 || len >= (ssize_t)sizeof(buffer)) {
        fprintf(stderr, "Error message for client %zu\n", client_id);
        return;
    }
    dprintf(my_server()->info.fds[client_id].fd, "%s\n", buffer);
}
