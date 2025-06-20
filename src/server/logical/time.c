/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** time
*/

#include "../includes/server.h"

double get_time(void)
{
    static time_t start_time = 0;
    time_t current_time;

    if (start_time == 0)
        start_time = time(NULL);
    current_time = time(NULL);
    return difftime(current_time, start_time) / my_server()->params.frequency;
}
