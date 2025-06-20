/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** communication
*/

#include "../includes/server.h"

void send_clients(int client_index, const char *message, va_list args)
{
    char buffer[BUFFER_SIZE];
    int len = vsnprintf(buffer, sizeof(buffer), message, args);

    if (len > 0 && len < BUFFER_SIZE) {
        dprintf(my_server()->info.fds[client_index].fd, "%s", buffer);
    } else {
        fprintf(stderr, "Message too long or formatting error\n");
    }
}

void send_to_all_clients(const char *message, va_list args)
{
    for (nfds_t i = 1; i < my_server()->info.fd_count; i++) {
        if (my_server()->info.fds[i].fd != -1) {
            send_clients(i, message, args);
        }
    }
}
