/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** gui_commands
*/
#include "./includes/server.h"
#include "./includes/gui.h"

void handle_msz(int client_fd, char **cmd)
{
    dprintf(client_fd, "msz %zu %zu\n", my_server()->params.width,
                                        my_server()->params.height);
    (void)cmd;
}

void handle_tna(int client_fd, char **cmd)
{
    for (size_t i = 0; my_server()->params.team_names[i]; i++) {
        dprintf(client_fd, "tna %s\n", my_server()->params.team_names[i]);
    }
    (void)cmd;
}
