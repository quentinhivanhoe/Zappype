/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_flags2
*/

#include "./includes/server.h"


void append_team_names(int argc, char **argv, int i)
{
    size_t team_count = 0;
    char **new_team_names;

    while (i < argc && argv[i][0] != '-') {
        new_team_names = realloc(my_server()->params.team_names,
        sizeof(char *) * (team_count + 2));
        if (!new_team_names) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        my_server()->params.team_names = new_team_names;
        my_server()->params.team_names[team_count] = strdup(argv[i]);
        if (!my_server()->params.team_names[team_count]) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        team_count++;
        i++;
    }
    my_server()->params.team_names[team_count] = NULL;
}

void add_team_names(int argc, char **argv, int i)
{
    if (my_server()->params.team_names) {
        fprintf(stderr, "Team names already set. Use -n only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        fprintf(stderr, "Team names are missing after -n flag\n");
        exit(EXIT_FAILURE);
    }
    my_server()->params.team_names = malloc(sizeof(char *));
    if (!my_server()->params.team_names) {
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
