/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** setup_server
*/

#include "../includes/server.h"
#include "../includes/clock.h"
bool check_event(void)
{
    for (nfds_t i = 0; i < my_server()->params.max_clients; i++) {
        if (!handle_event(i))
            return false;
    }
    return true;
}

void server_loop(void)
{
    int poll_ret = 0;
    double start_time = get_time();
    const double frame = 1 / my_server()->params.frequency;

    while (my_server()->running == true) {
        poll_ret = poll(my_server()->info.fds, my_server()->params.max_clients,
        1000 / my_server()->params.frequency);
        if (poll_ret < 0) {
            perror("poll");
            break;
        }
        if ((start_time + frame) < get_time() || !poll_ret) {
            clock_list(NULL, UPDATE);
            start_time = get_time();
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
            close(my_server()->info.fds[0].fd);
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

static void alloc_server(void)
{
    size_t size = my_server()->params.max_clients;
    size_t len_map = my_server()->params.width * my_server()->params.height;

    my_server()->info.fds = calloc(size, sizeof(struct pollfd));
    my_server()->info.clients = calloc(size, sizeof(client_t));
    my_server()->map = init_map(len_map);
}

static void set_default_fd(void)
{
    for (nfds_t i = 0; i < my_server()->params.max_clients; i++)
        my_server()->info.fds[i].fd = -1;
}

static int bind_server(void)
{
    if (bind(my_server()->info.fds[my_server()->info.fd_count].fd,
    (struct sockaddr *)&my_server()->info.address,
    sizeof(my_server()->info.address)) < 0) {
        perror("bind failed");
        clean_server();
        return -1;
    }
    if (listen(my_server()->info.fds[my_server()->info.fd_count].fd,
    my_server()->params.max_clients) < 0) {
        perror("listen");
        clean_server();
        return -1;
    }
    my_server()->running = true;
    return 0;
}

int setup_server(void)
{
    nfds_t count = my_server()->info.fd_count;

    if (my_server()->params.max_clients <= 0) {
        fprintf(stderr, "the maximum of clients must be great than 0\n");
        return -1;
    }
    alloc_server();
    if (!my_server()->info.fds || !my_server()->info.clients) {
        perror("calloc failed");
        return -1;
    }
    set_default_fd();
    my_server()->info.fds[count].fd = socket(AF_INET, SOCK_STREAM, 0);
    if (my_server()->info.fds[0].fd < 0) {
        perror("socket failed");
        return -1;
    }
    setup_address();
    return bind_server();
}
