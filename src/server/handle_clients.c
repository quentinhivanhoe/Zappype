/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_clients
*/

#include "./includes/server.h"
#include "./includes/gui.h"


void add_clients(int new_fd)
{
    my_server()->info.fds[my_server()->info.fd_count].fd = new_fd;
    my_server()->info.fds[my_server()->info.fd_count].events = POLLIN;
    (my_server()->info.fd_count)++;
    dprintf(new_fd, "Welcome to the server! You are client #%u\n",
        my_server()->info.fd_count - 1);
}

void handle_new_connection(void)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int new_fd;

    new_fd = accept(my_server()->info.fds[0].fd,
    (struct sockaddr *)&client_addr, &addr_len);
    if (new_fd < 0) {
        perror("accept");
        return;
    }
    if (my_server()->info.fd_count >= my_server()->params.max_clients + 1) {
        dprintf(new_fd, "Server is full. Try again later.\n");
        close(new_fd);
        return;
    }
    printf("New connection from %s:%d (client #%u)\n",
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port),
        my_server()->info.fd_count - 1);
    add_clients(new_fd);
}

void handle_client_data(int i)
{
    char buffer[BUFFER_SIZE];
    int nbytes;
    char resp[BUFFER_SIZE + 30];

    nbytes = read(my_server()->info.fds[i].fd, buffer, sizeof(buffer) - 1);
    if (nbytes <= 0) {
        if (nbytes == 0) {
            printf("Client #%d disconnected\n", i);
        } else {
            perror("read");
        }
        remove_client(i);
    } else {
        buffer[nbytes] = '\0';
        dispatch_command(my_server()->info.fds[i].fd, buffer);
        if (write(my_server()->info.fds[i].fd, resp, strlen(resp)) < 0) {
            perror("write");
        }
    }
}

void remove_client(int i)
{
    close(my_server()->info.fds[i].fd);
    if ((nfds_t)i < (my_server()->info.fd_count - 1)) {
        memmove(&my_server()->info.fds[i], &my_server()->info.fds[i + 1],
        sizeof(struct pollfd) * (my_server()->info.fd_count - i - 1));
    }
    my_server()->info.fd_count--;
}
