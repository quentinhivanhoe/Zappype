/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** time
*/

#include "../includes/server.h"

double get_elapsed_time_units_from_start(void)
{
    static time_t start_time = 0;
    time_t current_time;

    if (start_time == 0)
        start_time = time(NULL);
    current_time = time(NULL);
    // printf("Start time: %ld, Current time: %ld\n", start_time, current_time);
    return difftime(current_time, start_time) / my_server()->params.frequency;
}
