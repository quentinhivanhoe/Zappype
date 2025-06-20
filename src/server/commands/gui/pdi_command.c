/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pdi_command
*/
#include "../../includes/server.h"

void pdi_command(trn_t *trantorian)
{
    for (int fd = get_gui(); fd >= 0; fd = get_gui())
        dprintf(fd, "pdi #%d\n", trantorian->socket);
}
