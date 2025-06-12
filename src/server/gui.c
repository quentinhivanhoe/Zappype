/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_gui
*/

#include "./includes/server.h"
#include "./includes/gui.h"

static const char *gui_commands[] = {
    "msz\n",
    "tna\n",
    "ppo\n",
    NULL
};

static const gui_command_entry_t gui_command_table[] = {
    { "msz\n", handle_msz },
    { "tna\n", handle_tna },
    { NULL, NULL }
};

bool is_valid_command(const char *cmd)
{
    for (int i = 0; gui_commands[i] != NULL; i++) {
        if (strcmp(cmd, gui_commands[i]) == 0)
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
        args[count++] = strdup(token);
        token = strtok(NULL, " \n");
    }
    args = realloc(args, sizeof(char *) * (count + 1));
    args[count] = NULL;
    free(copy);
    return args;
}

void dispatch_command(int client_fd, const char *input)
{
    if (!input)
        return;
    char *line = strdup(input);
    if (!line)
        return;
    char *token = strtok(line, " \r\n");
    if (!token) {
        dprintf(client_fd, "Invalid command: %s", input);
        free(line);
        return;
    }
    for (nfds_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.clients[i].type == GUI) {
            for (int i = 0; gui_command_table[i].key != NULL; i++) {
                if (strncmp(gui_command_table[i].key, token, strlen(token)) == 0) {
                    char **args = split_args(input);
                    gui_command_table[i].handler(client_fd, args);
                    free(line);
                    return;
                }
            }
        }
    }
    dprintf(client_fd, "Invalid command: %s", input);
    free(line);
}
