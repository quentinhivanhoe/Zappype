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
    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next)
        if (cli->type == IA)
            decrease_food_bar(&cli->data.ia_client, cli->id);
}
