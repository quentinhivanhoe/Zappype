/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** parsing
*/

#ifndef PARSING_H_
    #define PARSING_H_
    #include <unistd.h>

typedef struct params_functions_s {
    char *flags;
    void (*function)(int, char **, int);
} params_functions_t;

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

#endif /* !PARSING_H_ */
