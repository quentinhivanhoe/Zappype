/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** end_game
*/
#include "../includes/server.h"
#include <stdbool.h>

bool seg_command(team_t *teams)
{
    size_t winner = 0;

    for (size_t i = 0; teams[i].name; i++) {
        if (teams[winner].dead < teams[i].dead)
            winner = i;
    }
    for (int fd = get_gui(); fd != -1; fd = get_gui())
        dprintf(fd, "seg %s\n", teams[winner].name);
    my_server()->running = false;
    return true;
}

bool end_game(team_t *teams)
{
    size_t deads = 0;
    size_t nbr = 0;

    for (; teams[nbr].name; nbr++) {
        if (teams[nbr].dead) {
            deads++;
            continue;
        }
        if (!teams[nbr].egg_count && !teams[nbr].trn_count) {
            teams[nbr].dead = get_time();
            deads++;
        }
    }
    if (nbr == deads)
        return seg_command(teams);
    return false;
}
