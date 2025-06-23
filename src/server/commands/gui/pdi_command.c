/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pdi_command
*/
#include "../../includes/server.h"

void pdi_command(size_t id)
{
    for (int fd = get_gui(); fd >= 0; fd = get_gui())
        dprintf(fd, "pdi #%ld\n", id);
}
