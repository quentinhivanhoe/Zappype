/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_flags
*/

#include "../includes/server.h"


void add_port(int argc, char **argv, int i)
{
    if (my_server()->params.port != 0) {
        fprintf(stderr, "Port number already set. Use -p only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc) {
        fprintf(stderr, "Port number is missing after -p flag\n");
        exit(EXIT_FAILURE);
    }
    if (!is_num(argv[i + 1])) {
        fprintf(stderr, "Invalid port number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
    }
    my_server()->params.port = atoi(argv[i + 1]);
}

void add_width(int argc, char **argv, int i)
{
    if (my_server()->params.width != 0) {
        fprintf(stderr, "Width number already set. Use -x only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc) {
        fprintf(stderr, "Width number is missing after -x flag\n");
        exit(EXIT_FAILURE);
    }
    if (!is_num(argv[i + 1])) {
        fprintf(stderr, "Invalid width number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
    }
    my_server()->params.width = atoi(argv[i + 1]);
}

void add_height(int argc, char **argv, int i)
{
    if (my_server()->params.height != 0) {
        fprintf(stderr, "Height number already set. Use -y only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc) {
        fprintf(stderr, "Height number is missing after -y flag\n");
        exit(EXIT_FAILURE);
    }
    if (!is_num(argv[i + 1])) {
        fprintf(stderr, "Invalid height number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
    }
    my_server()->params.height = atoi(argv[i + 1]);
}

void add_frequency(int argc, char **argv, int i)
{
    if (my_server()->params.frequency != 0) {
        fprintf(stderr, "Frequency number already set. Use -f only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc) {
        fprintf(stderr, "Frequency number is missing after -f flag\n");
        exit(EXIT_FAILURE);
    }
    if (!is_num(argv[i + 1])) {
        fprintf(stderr, "Invalid frequency number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
    }
    my_server()->params.frequency = atoi(argv[i + 1]);
}

void add_clients_nb(int argc, char **argv, int i)
{
    if (my_server()->params.max_clients != 0) {
        fprintf(stderr, "Clients number already set. Use -c only once.\n");
        exit(EXIT_FAILURE);
    }
    if (i + 1 >= argc) {
        fprintf(stderr, "Clients number is missing after -c flag\n");
        exit(EXIT_FAILURE);
    }
    if (!is_num(argv[i + 1])) {
        fprintf(stderr, "Invalid clients number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
    }
    my_server()->params.cli_per_team = atoi(argv[i + 1]);
}
