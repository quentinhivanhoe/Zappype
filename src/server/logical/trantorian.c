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
    if (!trantorian->inventory[FOOD]) {
            write(trantorian->socket, "dead\n", 5);
            pdi_command(i);
            if (my_server()->params.debug_mode)
                fprintf(stderr, "death of player #%d\n", trantorian->socket);
            remove_client(i);
    }
    trantorian->inventory[FOOD]--;
}

void trantorian_death(__attribute_maybe_unused__ clk_args_t *args)
{
    client_t *clients = my_server()->info.clients;
    size_t max_clients = my_server()->params.max_clients;

    for (size_t i = 0; i < max_clients; i++)
        if (clients[i].type == IA)
            decrease_food_bar(&clients[i].data.ia_client, i);
}

size_t get_trantorian_index(trn_t *trantorian)
{
    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.fds[i].fd == -1)
            continue;
        if (my_server()->info.clients[i].type == IA &&
            &my_server()->info.clients[i].data.ia_client == trantorian) {
            return i;
        }
    }
    return 0;
}
