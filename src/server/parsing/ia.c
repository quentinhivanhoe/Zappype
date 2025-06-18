/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia
*/

#include "../includes/server.h"
#include "../includes/ia.h"
#include "../includes/gui.h"

static const ia_cmd_t ia_command_table[] = {
    { "Forward", handle_forward, 7 },
    { "Right", handle_right, 7 },
    { "Left", handle_left, 7 },
    // { "Look", handle_look, 7 },
    { "Inventory", handle_inventory, 1 },
    // { "Broadcast", handle_broadcast, 7 },
    { "Connect_nbr", handle_connect_nbr, 0 },
    // { "Fork", handle_fork, 42 },
    // { "Eject", handle_eject, 7 },
    // { "Take", handle_take, 7 },
    // { "Set", handle_set, 7 },
    // { "Incantation", handle_incantation, 300 },
    { NULL, NULL, 0 }
};

static bool is_authorized_ia(int client_index, const char *input)
{
    int type = my_server()->info.clients[client_index].type;
    int fd = my_server()->info.fds[client_index].fd;

    if (type != IA) {
        dprintf(fd, "Unauthorized command for non-IA client: %s", input);
        return false;
    }
    return true;
}

static void free_args(char **args)
{
    if (!args)
        return;
    for (int j = 0; args[j]; j++)
        free(args[j]);
    free(args);
}

void handle_ia_command(trn_t *trantorian, const char *input, char *token)
{
    char **args = NULL;

    for (int i = 0; ia_command_table[i].cmd != NULL; i++) {
        if (strcmp(ia_command_table[i].cmd, token) == 0) {
            args = split_args(input);
            ia_command_table[i].handler(trantorian, args);
            free_args(args);
            return;
        }
    }
}

void dispatch_ia_command(int client_index, const char *input)
{
    int client_fd = my_server()->info.fds[client_index].fd;
    trn_t *trt = &my_server()->info.clients[client_index].data.ia_client;
    char *line = NULL;
    char *token = NULL;

    if (!input || !trt)
        return;
    line = strdup(input);
    if (!line)
        return;
    token = strtok(line, " \n");
    if (!token)
        return;
    if (!is_authorized_ia(client_index, input)) {
        free(line);
        return;
    }
    handle_ia_command(trt, input, token);
    free(line);
    (void)client_fd;
}
