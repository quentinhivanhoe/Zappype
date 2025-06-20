/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** signal
*/

#include "../includes/server.h"

void signal_handler(int signum)
{
    if (signum == SIGINT) {
        printf("\nServer shutting down...\n");
        my_server()->running = false;
    }
}
