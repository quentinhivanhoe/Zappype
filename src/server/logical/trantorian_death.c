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
