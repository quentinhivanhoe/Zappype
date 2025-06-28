/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia
*/

#include "../includes/server.h"
#include "../includes/ia.h"
#include "../includes/gui.h"

static const ia_cmd_t cmd_table[] = {
    { "Forward", handle_forward, 7 },
    { "Right", handle_right, 7 },
    { "Left", handle_left, 7 },
    { "Look", handle_look, 7 },
    { "Inventory", handle_inventory, 1 },
    { "Broadcast", handle_broadcast, 7 },
    { "Connect_nbr", handle_connect_nbr, 0 },
    { "Fork", handle_fork, 42 },
    { "Eject", handle_eject, 7 },
    { "Take", handle_take, 7 },
    { "Set", handle_set, 7 },
    { "Incantation", handle_incantation, 300 },
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

void handle_ia_command(trn_t *trn, const char *input, char *token)
{
    char **args = NULL;

    for (int i = 0; cmd_table[i].cmd != NULL; i++) {
        if (strcmp(cmd_table[i].cmd, token) == 0) {
            send_pic(trn, token);
            fprintf(stderr, "%s: added to the clock list\n", token);
            args = split_args(input);
            add_req(trn, args, cmd_table[i].handler, cmd_table[i].delay);
            return;
        }
    }
}

void dispatch_ia_command(int client_index, const char *input)
{
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
    fprintf(stderr, "token: %s", token);
    handle_ia_command(trt, input, token);
    free(line);
}
