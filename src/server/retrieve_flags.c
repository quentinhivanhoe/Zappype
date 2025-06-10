/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** retrieve_flags
*/

#include "./includes/server.h"

const params_functions_t params_functions[] = {
    {"-p", &add_port},
    {"-x", &add_width},
    {"-y", &add_height},
    {"-f", &add_frequency},
    {"-c", &add_clients_nb},
    {"-n", &add_team_names},
    {"-d", &set_debug_mode},
    {"--debug", &set_debug_mode},
    {"-h", &print_usage},
    {"--help", &print_usage},
    {NULL, NULL}
};

void execute_function(int argc, char **argv, int i)
{
    for (int j = 0; params_functions[j].flags != NULL; j++) {
        if (strcmp(argv[i], params_functions[j].flags) == 0
        && i < argc) {
            params_functions[j].function(argc, argv, i);
            break;
        }
    }
}

void det_params(int argc, char **argv)
{
    memset(&my_server()->params, 0, sizeof(my_server()->params));
    for (int i = 0; i < argc; i++) {
        execute_function(argc, argv, i);
    }
    my_server()->params.max_clients = my_server()->params.cli_per_team;
    my_server()->params.max_clients *= my_server()->params.team_nbr;
}

void check_params(void)
{
    if (my_server()->params.port == 0
    || my_server()->params.width == 0
    || my_server()->params.height == 0
    || my_server()->params.frequency == 0
    || my_server()->params.max_clients == 0
    || my_server()->params.team_names == NULL
    || my_server()->params.team_names[0] == NULL) {
        print_usage(0, NULL, 0);
    }
}

void print_params(void)
{
    printf("Server parameters:\n");
    printf("Port: %zu\n", my_server()->params.port);
    printf("Width: %zu\n", my_server()->params.width);
    printf("Height: %zu\n", my_server()->params.height);
    printf("Frequency: %zu\n", my_server()->params.frequency);
    printf("Max Clients: %zu\n", my_server()->params.max_clients);
    if (my_server()->params.team_names) {
        printf("Team Names:\n");
        for (size_t i = 0; my_server()->params.team_names[i] != NULL; i++) {
            printf(" - %s\n", my_server()->params.team_names[i]);
        }
    } else {
        printf("No team names provided.\n");
    }
    printf("Debug Mode: %s\n",
        my_server()->params.debug_mode ? "Enabled" : "Disabled");
}

void print_usage(int argc, char **argv, int i)
{
    (void)argc;
    (void)argv;
    (void)i;
    printf("Usage: ./server -p <port> -x <width> -y <height> ");
    printf("-f <frequency> -c <max_clients> ");
    printf("-n <team_name1> <team_name2> ...\n");
    printf("Options:\n");
    printf("  -p <port>          Set the port number n");
    printf("  -x <width>        Set the width of the map n");
    printf("  -y <height>       Set the height of the map n");
    printf("  -f <frequency>    Set the frequency of the server n");
    printf("  -c <max_clients>  Set the maximum number of clients n");
    printf("  -n <team_name1> <team_name2> ...  Set team names\n");
    exit(EXIT_FAILURE);
}
