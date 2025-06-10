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
    #define _GNU_SOURCE
    #define MAX_CLIENTS 5
    #define BUFFER_SIZE 1024
    #define PORT 8080
    #define OBJECT_DEFINED 7


typedef struct params_functions_s {
    char *flags;
    void (*function)(int, char **, int);
} params_functions_t;

typedef struct info_s {
    struct pollfd *fds;
    nfds_t fd_count;
    int port;
    struct sockaddr_in address;
} info_t;

typedef struct params_s {
    size_t port;
    size_t width;
    size_t height;
    size_t frequency;
    size_t cli_per_team;
    size_t max_clients;
    char **team_names;
    size_t team_nbr;
    bool debug_mode;
} params_t;

typedef struct server_s {
    info_t info;
    params_t params;
    bool running;
} server_t;

typedef uint64_t obj_t;

typedef enum object_index_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} obj_idx_t;

typedef enum direction_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
} dir_t;

typedef enum trantorian_status_e {
    ALIVE,
    DEAD,
    EGG,
    FROZEN
} trn_stat_t;

typedef struct position_s {
    uint64_t x;
    uint64_t y;
    dir_t dir;
} pos_t;

typedef struct trantorian_s {
    pos_t pos;
    uint8_t lvl;
    obj_t inventory[OBJECT_DEFINED];
    char *team;
    size_t wait_time;
    size_t clock;
    size_t food_bar;
    trn_stat_t stat;
    int socket;
} trn_t;

typedef struct tile_s {
    obj_t content[OBJECT_DEFINED];
} tile_t;

typedef enum client_type_e {
    GUI,
    IA,
    SERVER
} cli_type_t;

typedef union client_u {
    int socket;
    trn_t inhb;
} cli_t;

typedef struct client_list_s {
    cli_type_t type;
    cli_t data;
    struct cliet_list_s *next;
} cli_lst_t;


typedef struct trantor_s {
    tile_t **map;
    info_t info;
    params_t params;
    cli_lst_t *inhabitant;
    bool running;
} trt_t;

extern const params_functions_t params_functions[];
void add_clients(int new_fd);
void server_loop(void);
bool handle_event(int i);
trt_t *my_server(void);
int setup_server(void);
void clean_server(void);
void handle_new_connection(void);
void handle_client_data(int i);
void remove_client(int i);

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
