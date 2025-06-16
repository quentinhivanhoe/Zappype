/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia
*/

#include "../includes/server.h"
#include "../includes/ia.h"
#include "../includes/gui.h"


static const ia_cmd_t ia_command_table [] = {
    { "Forward", handle_forward, 7 },
    { NULL, NULL, 0 }
};

// bool is_valid_command_ia(const char *cmd)
// {
//     for (int i = 0; ia_command_table[i].cmd != NULL; i++) {
//         if (strcmp(cmd, ia_command_table[i].cmd) == 0)
//             return true;
//     }
//     return false;
// }

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

static void handle_ia_command(trn_t *trantorian, const char *input, const char *token)
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
    dprintf(trantorian->socket, "ko\n");
}

void dispatch_ia_command(int client_index, const char *input)
{
    __attribute_maybe_unused__ int client_fd = my_server()->info.fds[client_index].fd;
    trn_t *trantorian = &my_server()->info.clients[client_index].data.ia_client;
    char *line = NULL;
    char *token = NULL;

    if (!input || !trantorian)
        return;
    line = strdup(input);
    if (!line)
        return;
    token = strtok(line, " \n");
    if (!token) {
        free(line);
        return;
    }
    if (!is_authorized_ia(client_index, input)) {
        free(line);
        return;
    }
    handle_ia_command(trantorian, input, token);
    free(line);
}
