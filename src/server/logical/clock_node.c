/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** handle_clock
*/
#include "../includes/time.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

clk_node_t *alloc_node(size_t limit, callback_t call, void *arg, uint64_t flag)
{
    clk_node_t *node = NULL;

    if (!call) {
        fprintf(stderr, "%s: callback is null\n", __FILE__);
        return node;
    }
    node = calloc(1, sizeof(clk_node_t));
    if (!node) {
        fprintf(stderr, "%s: %s\n", __FILE__, strerror(errno));
        exit(84);
    }
    node->callback = call;
    node->args = arg;
    node->frame_limit = limit;
    node->flags = flag;
}
