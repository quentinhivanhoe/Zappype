/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** clock_list
*/
#include "../includes/clock.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

static sll_t *alloc_list(void)
{
    sll_t *list = calloc(1, sizeof(sll_t));

    if (!list) {
            fprintf(stderr, "%s: %s\n", __FILE__, strerror(errno));
            exit(84);
    }
    return list;
}

static void del_clock(sll_t **list)
{
    sll_t *list_to_free = (*list);

    if (!list)
        return;
    if (!(*list))
        return;
    if ((*list)->prev)
        (*list)->prev->next = (*list)->next;
    if ((*list)->next)
        (*list)->next->prev = (*list)->prev;
    if ((*list)->node->args)
        free((*list)->node->args);
    if ((*list)->node)
        free((*list)->node);
    if ((*list)->prev)
        (*list) = (*list)->prev;
    if ((*list)->next)
        (*list) = (*list)->next;
    free(list_to_free);
}

static void run_event(sll_t **list)
{
    (*list)->node->frame_counter++;
    if ((*list)->node->frame_limit > (*list)->node->frame_counter)
        return;
    (*list)->node->callback((*list)->node->args);
    if (!((*list)->node->flags & LOOP_CLOCK))
        del_clock(list);
    else
        (*list)->node->frame_counter = 0;
}

void add_clock(sll_t **list, clk_node_t *node)
{
    sll_t *new = NULL;

    if (!(node->flags & ARGS_UNUSED)) {
        if (node->args->trantorian->req_count >= 10) {
            free(node->args);
            free(node);
            return;
        }
        node->args->trantorian->req_count++;
    }
    new = alloc_list();
    new->node = node;
    new->next = (*list);
    if ((*list))
        (*list)->prev = new;
    (*list) = new;
}

void destroy_clock(sll_t **list)
{
    sll_t *next = NULL;

    if (!list)
        return;
    while ((*list)) {
        next = (*list)->next;
        del_clock(list);
        (*list) = next;
    }
}

void update_clock(sll_t **list)
{
    if (!list)
        return;
    if (!(*list))
        return;
    fprintf(stderr, "updating !\n");
    while ((*list)) {
        run_event(list);
        if (!(*list)->next)
            break;
        (*list) = (*list)->next;
    }
    if ((*list))
        while ((*list)->prev)
            (*list) = (*list)->prev;
    fprintf(stderr, "finish updating !\n");
}

void clock_list(clk_node_t *node, clk_act_t action)
{
    static sll_t *list = NULL;

    if (action == ADD && node)
        add_clock(&list, node);
    if (action == DESTROY)
        destroy_clock(&list);
    if (action == UPDATE)
        update_clock(&list);
    return;
}
