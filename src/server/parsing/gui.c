/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_gui
*/

#include "../includes/server.h"
#include "../includes/gui.h"

// static const char *gui_commands[] = {
//     "msz",
//     "tna",
//     "ppo",
//     "mct",
//     "bct",
//     NULL
// };

static const gui_command_entry_t gui_command_table[] = {
    { "msz", handle_msz },
    { "tna", handle_tna },
    { "mct", handle_mct },
    { "bct", handle_bct },
    { "ppo", handle_ppo },
    { NULL, NULL }
};

bool is_valid_command(const char *cmd)
{
    for (int i = 0; gui_command_table[i].key != NULL; i++) {
        if (strcmp(cmd, gui_command_table[i].key) == 0)
            return true;
    }
    return false;
}

char **split_args(const char *cmd)
{
    char *copy = strdup(cmd);
    char **args = NULL;
    int count = 0;
    char *token = strtok(copy, " \n");

    while (token != NULL) {
        args = realloc(args, sizeof(char *) * (count + 1));
        args[count] = strdup(token);
        count++;
        token = strtok(NULL, " \n");
    }
    args = realloc(args, sizeof(char *) * (count + 1));
    printf("count: [%d]\n", count);
    args[count] = NULL;
    free(copy);
    return args;
}

static bool is_authorized_gui(int client_index, const char *input)
{
    int type = my_server()->info.clients[client_index].type;
    int fd = my_server()->info.fds[client_index].fd;

    if (type != GUI) {
        dprintf(fd, "Unauthorized command for non-GUI client: %s", input);
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

static void handle_gui_command(int fd, const char *input, const char *token)
{
    char **args = NULL;

    for (int i = 0; gui_command_table[i].key != NULL; i++){
        if (strcmp(gui_command_table[i].key, token) == 0) {
            args = split_args(input);
            gui_command_table[i].handler(fd, args);
            free_args(args);
            return;
        }
    }
    dprintf(fd, "Invalid GUI command: %s", input);
}

void dispatch_command(int client_index, const char *input)
{
    int client_fd = my_server()->info.fds[client_index].fd;
    char *line = NULL;
    char *token = NULL;

    if (!input)
        return;
    line = strdup(input);
    if (!line)
        return;
    token = strtok(line, " \n");
    if (!token) {
        free(line);
        return;
    }
    if (!is_authorized_gui(client_index, input)) {
        free(line);
        return;
    }
    handle_gui_command(client_fd, input, token);
    free(line);
}
