/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** spn_commadn
*/
#include "../../includes/server.h"

void spn_command(int client_fd, __attribute_maybe_unused__ char **cmd)
{
    dprintf(client_fd, "pnu %ld\n", my_server()->info.trn_count);
}
