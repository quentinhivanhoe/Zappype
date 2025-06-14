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
    #define LOOP_CLOCK 1
    #define ONE_SHOT_CLOCK 2

typedef enum clock_action_e {
    ADD,
    UPDATE,
    DESTROY
} clk_act_t;

typedef void (*callback_t)(void *);

typedef struct clock_node_s {
    size_t frame_counter;
    size_t frame_limit;
    callback_t callback;
    uint64_t flags;
    void *args
} clk_node_t;

typedef struct singly_linked_list_s {
    clk_node_t *node;
    struct singly_linked_list_s *prev;
    struct singly_linked_list_s *next;
} sll_t;
clk_node_t *alloc_node(size_t limit, callback_t call, void *arg, uint64_t flag);

#endif /* !TIME_H_ */
