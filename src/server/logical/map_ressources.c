/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** handle_map
*/

#include "../includes/trantor.h"
#include "../includes/server.h"
#include "../includes/clock.h"
#include <stdlib.h>
#include <stdio.h>

const float density_table[OBJECT_DEFINED + 1] = {
    0.5,
    0.3,
    0.15,
    0.1,
    0.1,
    0.08,
    0.05,
    0
};

static void set_obj_number(uint64_t *number, size_t size)
{
    for (uint8_t i = 0; density_table[i]; i++)
        number[i] = (uint64_t)(size * density_table[i]);
}

static void set_padding(uint64_t *padding, uint64_t *object, size_t size)
{
    for (uint8_t i = 0; i < OBJECT_DEFINED; i++)
        padding[i] = size / object[i];
}

tile_t fill_tile(uint64_t *object, uint64_t *padding, size_t idx)
{
    tile_t tile = {0};

    for (uint8_t i = 0; i < OBJECT_DEFINED; i++) {
        if (idx % padding[i] == 0 && object[i]) {
            tile.content[i] = 1;
            object[i]--;
        }
    }
    return tile;
}

tile_t *dispatch_object(uint64_t *object, uint64_t *padding, size_t size)
{
    tile_t *map = NULL;

    map = calloc(size, sizeof(tile_t));
    if (!map) {
        perror("dispatch_objetc: calloc");
        exit(84);
    }
    for (size_t i = 0; i < size; i++)
        map[i] = fill_tile(object, padding, i);
    return map;
}

void respwan_ressoruces(__attribute_maybe_unused__ clk_args_t *args)
{
    int rand_pos = 0;
    size_t len_map = my_server()->params.width * my_server()->params.height;

    for (size_t i = 0; i < OBJECT_DEFINED; i++) {
        srand(get_time());
        rand_pos = rand() % len_map;
        my_server()->map[rand_pos].content[i] += 1;
    }
    if (my_server()->params.debug_mode)
        fprintf(stderr, "ressources have respawn\n");
}

tile_t *init_map(size_t len_map)
{
    uint64_t object[OBJECT_DEFINED] = {0};
    uint64_t padding[OBJECT_DEFINED] = {0};
    clk_node_t *node = NULL;
    clk_args_t *args = NULL;

    set_obj_number(object, len_map);
    set_padding(padding, object, len_map);
    args = alloc_args(NULL, NULL, 20, LOOP_CLOCK | ARGS_UNUSED);
    node = alloc_node(respwan_ressoruces, args);
    clock_list(node, ADD);
    return dispatch_object(object, padding, len_map);
}
