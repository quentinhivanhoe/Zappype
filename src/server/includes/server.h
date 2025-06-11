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
    #include <signal.h>
    #include "parsing.h"
    #include "trantor.h"
    #include "client.h"
    #define _GNU_SOURCE
    #define MAX_CLIENTS 5
    #define BUFFER_SIZE 1024
    #define PORT 8080

typedef struct network_s {
    struct pollfd *fds;
    client_t *clients;
    nfds_t fd_count;
    int port;
    struct sockaddr_in address;
} ntw_t;

typedef struct server_s {
    ntw_t info;
    params_t params;
    tile_t *map;
    bool running;
} server_t;

void add_clients(int new_fd);
void server_loop(void);
bool handle_event(int i);
server_t *my_server(void);
int setup_server(void);
void clean_server(void);
void handle_new_connection(void);
void handle_client_data(int i);
void remove_client(int i);

/* Registration process*/

void register_gui_client(int i);
void process_ia_connection(int i, int team_index);
void register_ia_client(int i, char *team_name);
void det_teams(char *buffer, int i);
/* UTIL */
bool is_num(const char *str);

/* FLAGS FUNCTIONS */
void add_port(int argc, char **argv, int i);
void add_width(int argc, char **argv, int i);
void add_height(int argc, char **argv, int i);
void add_frequency(int argc, char **argv, int i);
void add_clients_nb(int argc, char **argv, int i);
void add_team_names(int argc, char **argv, int i);
void set_debug_mode(int argc, char **argv, int i);
void print_usage(int argc, char **argv, int i);
void append_team_names(int argc, char **argv, int i);
void check_params(void);
void det_params(int argc, char **argv);
void print_params(void);

/* SIGNAL */
void signal_handler(int signum);

#endif /* !SERVER_H_ */
