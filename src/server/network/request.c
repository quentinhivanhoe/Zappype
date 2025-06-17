/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** request
*/
#include "../includes/trantor.h"
#include "../includes/server.h"
#include "../includes/gui.h"

void add_req(trn_t *trn, char **args, req_func_t func, size_t delay)
{
    if (!trn)
        return;
    if (trn->req_count >= MAX_REQUEST)
        return;
    trn->req_queue[trn->req_count].callback = func;
    trn->req_queue[trn->req_count].delay = delay;
    trn->req_queue[trn->req_count].args = args;
    trn->req_count++;
}

void unqueue(req_queue_t *queue, size_t count)
{
    for (size_t n = 0; (n +1) < count; n++)
        queue[n] = queue[n + 1];
}

void run_req(trn_t *trn)
{
    if (trn->socket > 0) {
        if (!trn->req_count)
            return;
        trn->frame_count++;
        if (trn->frame_count >= trn->req_queue[0].delay) {
            trn->req_queue[0].callback(trn, trn->req_queue[0].args);
            free_args(trn->req_queue[0].args);
            unqueue(trn->req_queue, trn->req_count);
            trn->req_count--;
            trn->frame_count = 0;
        }
    }
}

void parse_req(void)
{
    client_t *clients = my_server()->info.clients;

    for (size_t i = 1; i < my_server()->params.max_clients; i++) {
        if (clients[i].type == IA)
            run_req(&clients[i].data.ia_client);
    }
}
