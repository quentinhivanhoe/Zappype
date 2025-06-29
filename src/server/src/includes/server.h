/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <poll.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #define MAX_CLIENTS 5
    #define BUFFER_SIZE 1024
    #define PORT 8080


typedef struct info_s {
    int server_fd;
    struct pollfd fds[MAX_CLIENTS + 1];
    int fd_count;
    int port;
    struct sockaddr_in address;
} info_t;


typedef struct server_s {
    info_t info;
} server_t;

void add_clients(int new_fd);
void server_loop(void);
bool handle_event(int i);
server_t *my_server(void);
int setup_server(void);
void handle_new_connection(void);
void handle_client_data(int i);
void remove_client(int i);

#endif /* !SERVER_H_ */
