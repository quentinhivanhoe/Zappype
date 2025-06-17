/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** handle_clock
*/
#include "../includes/clock.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

clk_node_t *alloc_node(callback_t call, clk_args_t *args)
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
    node->args = args;
    node->frame_limit = args->limit;
    node->flags = args->flag;
    return node;
}

clk_args_t *alloc_args(trn_t *trn, char **argv, size_t limit, uint64_t flags)
{
    clk_args_t *args = calloc(1, sizeof(clk_args_t));

    if (!args) {
        fprintf(stderr, "%s: %s", __FILE__, strerror(errno));
        exit(EXIT_FAILURE);
    }
    args->flag = flags;
    args->limit = limit;
    if ((flags & ARGS_UNUSED))
        return args;
    args->args = argv;
    args->trantorian = trn;
    return args;
}