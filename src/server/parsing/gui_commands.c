/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** gui_commands
*/
#include "../includes/server.h"
#include "../includes/gui.h"

void handle_msz(int client_fd, char **cmd)
{
    dprintf(client_fd, "msz %zu %zu\n", my_server()->params.width,
                                        my_server()->params.height);
    (void)cmd;
}

void handle_tna(int client_fd, char **cmd)
{
    for (size_t i = 0; my_server()->params.team_names[i]; i++) {
        dprintf(client_fd, "tna %s\n", my_server()->params.team_names[i]);
    }
    (void)cmd;
}

void handle_mct(int client_fd, __attribute_maybe_unused__ char **cmd)
{
    size_t width = my_server()->params.width;
    size_t height = my_server()->params.height;
    tile_t tile = {0};

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            tile = get_object(my_server()->map, i, j);
            dprintf(client_fd,
                "bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", i, j,
                tile.content[FOOD],
                tile.content[LINEMATE],
                tile.content[DERAUMERE],
                tile.content[SIBUR],
                tile.content[MENDIANE],
                tile.content[PHIRAS],
                tile.content[THYSTAME]
            );
        }
    }
}
