/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** setup_team
*/
#include "../includes/server.h"

trn_t init_egg(size_t team_id)
{
    trn_t egg = {0};

    srand(time(NULL));
    egg.pos.x = rand() % my_server()->params.width;
    egg.pos.y = rand() % my_server()->params.height;
    egg.pos.dir = (rand() % 4) + 1;
    egg.socket = -1;
    egg.team_id = team_id;
    egg.lvl = 1;
    egg.inventory[FOOD] = 10;
    return egg;
}

void setup_team(void)
{
    client_t *clients = my_server()->info.clients;
    struct pollfd *fds = my_server()->info.fds;
    size_t egg_nbr = my_server()->params.cli_per_team;

    for (size_t i = 0; my_server()->params.teams[i].name; i++) {
        for (size_t j = 0; j < egg_nbr; j++) {
            my_server()->params.teams[i].egg_count++;
            clients[(i * egg_nbr) + (j + 1)].type = EGG;
            clients[(i * egg_nbr) + (j + 1)].data.ia_client = init_egg(i);
            fds[(i * egg_nbr) + (j + 1)].fd = 0;
        }
    }
}
