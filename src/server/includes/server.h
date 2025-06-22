/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #define _GNU_SOURCE
    #include <time.h>
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
    size_t trn_count;
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
void setup_team(void);
int setup_server(void);
void clean_server(void);
void handle_new_connection(void);
void handle_client_data(int i);
void remove_client(int i);

/* Singleton */
client_t *get_client(size_t client_idx);
server_t *my_server(void);

/* Time management function */
double get_time(void);

/* Registration process*/

void register_gui_client(int i);
void process_ia_connection(client_t *clients, int i, size_t team_index);
void register_ia_client(int i, char *team_name);
void det_teams(char *buffer, int i);
/* UTIL */
bool is_num(const char *str);

/* SIGNAL */
void signal_handler(int signum);

int get_gui(void);
void pdi_command(trn_t *trantorian);
size_t count_ia_clients(size_t id);
void pnw_command(trn_t trantorian);
void spn_command(int client_fd, __attribute_maybe_unused__ char **cmd);
void pls_command(int client_fd, char **cmd);
void pdr_command(int player_id, obj_idx_t object);
void pgt_command(int player_id, obj_idx_t object);

#endif /* !SERVER_H_ */
