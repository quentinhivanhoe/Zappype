/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** setup_team
*/
#include "../includes/server.h"

void setup_team(void)
{
    client_t *clients = my_server()->info.clients;

    for (size_t i = 0; my_server()->params.teams[i].name; i++) {
        my_server()->params.teams[i].max = my_server()->params.cli_per_team;
        my_server()->params.teams[i].egg_count++;
        clients[i + 1].type = EGG;
    }
}