/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** gui_commands_1
*/

#include <stdio.h>
#include <unistd.h>

void handle_msz(int client_fd)
{
    dprintf(client_fd, "Execution of command: msz\n");
}

void handle_mct(int client_fd)
{
    dprintf(client_fd, "Execution of command: mct\n");
}

void handle_bct(int client_fd)
{
    dprintf(client_fd, "Execution of command: bct\n");
}

void handle_ppo(int client_fd)
{
    dprintf(client_fd, "Execution of command: ppo\n");
}

void handle_spn(int client_fd)
{
    dprintf(client_fd, "Execution of command: spn\n");
}

void handle_spp(int client_fd)
{
    dprintf(client_fd, "Execution of command: spp\n");
}