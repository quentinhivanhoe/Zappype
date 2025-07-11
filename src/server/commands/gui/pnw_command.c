/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** pnw_command
*/
#include "../../includes/server.h"

void pnw_command(trn_t trantorian, size_t id)
{
    pos_t pos = {0};
    uint8_t lvl = 0;
    char *team = NULL;
    int gui_fd = 0;

    if (trantorian.socket < 0)
        return;
    pos = trantorian.pos;
    lvl = trantorian.lvl;
    team = my_server()->params.teams[trantorian.team_id].name;
    for (gui_fd = get_gui(); gui_fd >= 0; gui_fd = get_gui())
        dprintf(gui_fd, "pnw #%ld %ld %ld %d %d %s\n",
            id, pos.x, pos.y, pos.dir, lvl, team);
    if (my_server()->params.debug_mode)
        fprintf(stderr, "New IA client: pos=(%lu, %lu), dir=%d\n",
            pos.x, pos.y, pos.dir);
}
