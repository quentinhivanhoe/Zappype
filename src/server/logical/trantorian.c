/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** trantorian_death
*/
#include "../includes/clock.h"
#include "../includes/server.h"

void decrease_food_bar(trn_t *trantorian, size_t i)
{
    trantorian->food_bar--;
    if (!trantorian->food_bar) {
            write(trantorian->socket, "dead\n", 5);
            pdi_command(trantorian);
            if (my_server()->params.debug_mode)
                fprintf(stderr, "death of player #%d\n", trantorian->socket);
            remove_client(i);
    }
}

void trantorian_death(__attribute_maybe_unused__ clk_args_t *args)
{
    client_t *clients = my_server()->info.clients;
    size_t max_clients = my_server()->params.max_clients;

    for (size_t i = 0; i < max_clients; i++)
        if (clients[i].type == IA)
            decrease_food_bar(&clients[i].data.ia_client, i);
}

void init_trantorian(trn_t *trantorian, int i, int team_index)
{
    srand(time(NULL));
    trantorian->pos.x = rand() % my_server()->params.width;
    trantorian->pos.y = rand() % my_server()->params.height;
    trantorian->pos.dir = (rand() % 4) + 1;
    trantorian->lvl = 1;
    trantorian->socket = my_server()->info.fds[i].fd;
    trantorian->food_bar = 1260;
    my_server()->info.clients[i].type = IA;
    my_server()->info.clients[i].data.ia_client.team_id = team_index;
    my_server()->info.trn_count++;
    pnw_command(trantorian);
}
