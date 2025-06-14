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
    if (!list)
        return;
    if (!(*list))
        return;
    if ((*list)->prev)
        (*list)->prev->next = (*list)->next;
    if ((*list)->next)
        (*list)->next->prev = (*list)->prev;
    if ((*list)->node)
        free((*list)->node);
    free((*list));
}

static void run_event(sll_t **list)
{
    if (!((*list)->node->flags & LOOP_CLOCK))
        del_clock(list);
    (*list)->node->frame_counter = 0;
    (*list)->node->callback((*list)->node->args);
}

void add_clock(sll_t **list, clk_node_t *node)
{
    sll_t *new = NULL;

    if (!list || !node) {
        if (node)
            free(node);
        return;
    }
    new = alloc_list();
    new->node = node;
    new->next = (*list);
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
    sll_t *parse_ptr = NULL;

    if (!list)
        return;
    if (!(*list))
        return;
    fprintf(stderr, "updating !\n");
    parse_ptr = (*list);
    while (parse_ptr) {
        parse_ptr->node->frame_counter++;
        if (parse_ptr->node->frame_limit == parse_ptr->node->frame_counter)
            run_event(&parse_ptr);
        parse_ptr = parse_ptr->next;
    }
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
