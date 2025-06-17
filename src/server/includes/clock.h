/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** time
*/

#ifndef TIME_H_
    #define TIME_H_
    #include <stdlib.h>
    #include <stdint.h>
    #include "trantor.h"
    #define LOOP_CLOCK 1
    #define ONE_SHOT_CLOCK 2
    #define ARGS_UNUSED 4

typedef enum clock_action_e {
    ADD,
    UPDATE,
    DESTROY
} clk_act_t;

typedef struct clock_args_s {
    trn_t *trantorian;
    char **args;
    size_t limit;
    uint64_t flag;
} clk_args_t;

typedef void (*callback_t)(clk_args_t *);

typedef struct clock_node_s {
    size_t frame_counter;
    size_t frame_limit;
    callback_t callback;
    uint64_t flags;
    clk_args_t *args;
} clk_node_t;

typedef struct singly_linked_list_s {
    clk_node_t *node;
    struct singly_linked_list_s *prev;
    struct singly_linked_list_s *next;
} sll_t;

clk_node_t *alloc_node(callback_t call, clk_args_t *args);
clk_args_t *alloc_args(trn_t *trn, char **argv, size_t limit, uint64_t flags);
void clock_list(clk_node_t *node, clk_act_t action);

#endif /* !TIME_H_ */
