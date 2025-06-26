/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** client
*/
#include "../includes/client.h"
#include "../includes/server.h"
#include <stdlib.h>


void add_list(client_t **list, client_type_t type, int fd, trn_t trn)
{
    client_t *client = calloc(1, sizeof(client_t));
    client_t *tmp = (*list);
    size_t id = 1;

    client->type = type;
    if (client->type == GUI)
        client->data.gui_client = fd;
    else
        client->data.ia_client = trn;
    client->id = id;
    if (!tmp) {
        (*list) = client;
        return;
    }
    for (id++; tmp->next; id++)
        tmp = tmp->next;
    client->id = id;
    tmp->next = client;
}

client_t *get_client_by_id(size_t id)
{
    for (client_t *cli = my_server()->info.clients; cli; cli = cli->next) {
        fprintf(stderr, "parse id: %ld\n", cli->id);
        if (cli->id == id)
            return cli;
    }
    return NULL;
}
