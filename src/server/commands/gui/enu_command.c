/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** enu_command
*/
#include "../../includes/server.h"

void enu_command(int client_fd, __attribute_maybe_unused__ char **cmd)
{
    team_t *teams = my_server()->params.teams;
    size_t egg_nbr = 0;

    for (size_t i = 0; my_server()->params.teams[i].name; i++)
        egg_nbr += teams[i].egg_count;
    dprintf(client_fd, "enu %ld\n", egg_nbr);
    return;
}
