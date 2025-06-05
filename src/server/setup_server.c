/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** setup_server
*/

#include "./includes/server.h"

bool check_event(void)
{
    for (int i = 0; i < my_server()->info.fd_count; i++) {
        if (!handle_event(i))
            return false;
    }
    return true;
}

void server_loop(void)
{
    while (my_server()->running == true) {
        if (poll(my_server()->info.fds, my_server()->info.fd_count, -1) < 0) {
            perror("poll");
            break;
        }
        if (!check_event())
            break;
    }
}

bool handle_event(int i)
{
    if (my_server()->info.fds[i].revents == 0)
        return true;
    if (my_server()->info.fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        if (i != 0) {
            printf("Client disconnected due to error\n");
            remove_client(i);
        } else {
            perror("Server socket error");
            close(my_server()->info.server_fd);
            return false;
        }
        return true;
    }
    if (my_server()->info.fds[i].revents & POLLIN) {
        if (i == 0) {
            handle_new_connection();
        } else
            handle_client_data(i);
    }
    return true;
}

static void setup_address(void)
{
    my_server()->info.address.sin_family = AF_INET;
    my_server()->info.address.sin_addr.s_addr = INADDR_ANY;
    my_server()->info.address.sin_port = htons(my_server()->info.port);
}

int setup_server(void)
{
    my_server()->info.server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (my_server()->info.server_fd < 0) {
        perror("socket failed");
        return -1;
    }
    setup_address();
    if (bind(my_server()->info.server_fd,
    (struct sockaddr *)&my_server()->info.address,
    sizeof(my_server()->info.address)) < 0) {
        perror("bind failed");
        close(my_server()->info.server_fd);
        return -1;
    }
    if (listen(my_server()->info.server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(my_server()->info.server_fd);
        return -1;
    }
    my_server()->running = true;
    return 0;
}

server_t *my_server(void)
{
    static server_t server;

    return &server;
}
