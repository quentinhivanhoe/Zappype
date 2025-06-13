/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** handle_map2
*/

#include "../includes/server.h"

size_t get_index(ssize_t x, ssize_t y)
{
    size_t width = my_server()->params.width;
    size_t height = my_server()->params.height;
    size_t norm_x = (x % width + width) % width;
    size_t norm_y = (y % height + height) % height;
    size_t index = norm_y * width + norm_x;

    return index;
}

tile_t get_object(tile_t *tile, ssize_t x, ssize_t y)
{
    return tile[get_index(x, y)];
}
