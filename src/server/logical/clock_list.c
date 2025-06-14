/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** clock_list
*/
#include "../includes/time.h"
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
    new->next = (*list)->next ? (*list)->next : NULL;
    (*list) = new;
}

void update_clock(sll_t **list)
{
    sll_t *parse_ptr = NULL;

    if (!list)
        return;
    if (!(*list))
        return;
    parse_ptr = (*list);
    while (parse_ptr) {
        parse_ptr->node->frame_counter++;
        if (parse_ptr->node->frame_limit == parse_ptr->node->frame_counter) {
            if (!(parse_ptr->node->flags & LOOP_CLOCK))
                del_clock(&parse_ptr);
            parse_ptr->node->frame_counter = 0;
            parse_ptr->node->callback(parse_ptr->node->args);
        }
    }
}

void del_clock(sll_t **list)
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

void destroy_clock(sll_t **list)
{
    if (!list)
        return;
    if (!(*list))
        return;
    while ((*list)) {
        del_clock(&(*list)->next);
        (*list) = (*list)->next;
    }
}

void clock_list(clk_node_t *node, clk_act_t action)
{
    static sll_t *list = NULL;

    if (action == ADD && node)
        add_clock(&list, node);
    if (action == DESTROY && node)
        destroy_clock(&list);
    if (action == UPDATE)
        update_clock(&list);
    return;
}