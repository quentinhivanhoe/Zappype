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

#endif /* !PARSING_H_ */
