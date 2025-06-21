/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_flags2
*/

#include "../includes/server.h"


void append_team_names(int argc, char **argv, int i)
{
    size_t cmp = 0;
    team_t *teams = NULL;

    for (; i < argc && argv[i][0] != '-'; i++) {
        teams = realloc(my_server()->params.teams, sizeof(team_t) * (cmp + 2));
        if (!teams) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        my_server()->params.teams = teams;
        memset(&my_server()->params.teams[cmp], 0, sizeof(team_t));
        my_server()->params.teams[cmp].name = strdup(argv[i]);
        if (!my_server()->params.teams[cmp].name) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        cmp++;
    }
    my_server()->params.team_nbr = cmp + 1;
    my_server()->params.teams[cmp].name = NULL;
}

void add_team_names(int argc, char **argv, int i)
{
    if (my_server()->params.teams) {
        fprintf(stderr, "Team names already set. Use -n only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        fprintf(stderr, "Team names are missing after -n flag\n");
        exit(EXIT_FAILURE);
    }
    my_server()->params.teams = malloc(sizeof(team_t));
    if (!my_server()->params.teams) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    i++;
    append_team_names(argc, argv, i);
}

void set_debug_mode(int argc, char **argv, int i)
{
    (void)argc;
    (void)argv;
    (void)i;
    my_server()->params.debug_mode = true;
}
