/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** gui_commands_1
*/

#include <stdio.h>
#include <unistd.h>
#include "./includes/server.h"

void handle_msz(int client_fd)
{
    dprintf(client_fd, "msz %zu %zu\n", my_server()->params.width,
                                    my_server()->params.height);
}

void handle_tna(int client_fd)
{
    if (my_server()->params.team_names) {
        for (size_t i = 0; my_server()->params.team_names[i] != NULL; i++) {
            dprintf(client_fd, "tna %s\n", my_server()->params.team_names[i]);
        }
    }
}

void handle_ppo(int client_fd, )
