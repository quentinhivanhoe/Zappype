/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_clients
*/

#include "../includes/server.h"
#include "../includes/gui.h"
#include "../includes/ia.h"

void add_clients(int new_fd)
{
    int free_slots = -1;

    for (nfds_t i = 1; i < my_server()->params.max_clients + 1; i++) {
        if (my_server()->info.fds[i].fd == -1) {
            free_slots = i;
            break;
        }
    }
    if (free_slots == -1) {
        fprintf(stderr, "No free slots available for new client.\n");
        close(new_fd);
        return;
    }
    my_server()->info.fds[free_slots].fd = new_fd;
    my_server()->info.fds[free_slots].events = POLLIN;
    (my_server()->info.fd_count)++;
    dprintf(new_fd, "WELCOME\n");
    my_server()->info.clients[free_slots].type = UNDEFINED;
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
    if (my_server()->params.debug_mode)
        dprintf(2, "New connection from %s:%d (client #%lu)\n",
        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
        my_server()->info.fd_count - 1);
    add_clients(new_fd);
}

void parse_data(char *buffer, int i)
{
    if (my_server()->params.debug_mode)
        dprintf(2, "Received from client #%d: %s", i, buffer);
    if (my_server()->info.clients[i].type == UNDEFINED) {
        dprintf(STDERR_FILENO, "user not authentified, define teams\n");
        det_teams(buffer, i);
        return;
    }
    if (my_server()->info.clients[i].type == GUI)
        dispatch_command(i, buffer);
    else if (my_server()->info.clients[i].type == IA)
        dispatch_ia_command(i, buffer);
    else
        dprintf(my_server()->info.fds[i].fd, "Unknown client type\n");
}

void handle_client_data(int i)
{
    char buffer[BUFFER_SIZE];
    int nbytes;

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
        parse_data(buffer, i);
    }
}

void remove_client(int i)
{
    close(my_server()->info.fds[i].fd);
    my_server()->info.fds[i].fd = -1;
    my_server()->info.fds[i].events = 0;
    my_server()->info.fd_count--;
}
