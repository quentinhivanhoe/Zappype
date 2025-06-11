/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** handle_gui
*/

#include "./includes/server.h"
#include "./includes/handle_gui.h"

static const char *gui_commands[] = {
    "msz\n",
    // "bct\n",
    // "mct\n",
    "tna\n",
    "ppo\n",
    // "plv\n",
    // "pin\n",
    // "sgt\n",
    // "sst\n",
    // "spn\n",
    NULL
};

static const gui_command_entry_t gui_command_table[] = {
    { "msz\n", handle_msz },
    { "tna\n", handle_tna },
    // { "mct\n", handle_mct },
    // { "bct\n", handle_bct },
    { "ppo\n", handle_ppo },
    // { "spn\n", handle_spn },
    // { "spp\n", handle_spp },
    { NULL, NULL }
};

bool is_valid_command(const char *cmd)
{
    for (int i = 0; gui_commands[i] != NULL; i++) {
        if (strcmp(cmd, gui_commands[i]) == 0)
            return true;
    }
    return false;
}

void dispatch_command(int client_fd, const char *cmd)
{
    for (int i = 0; gui_command_table[i].key != NULL; i++) {
        if (strcmp(gui_command_table[i].key, cmd) == 0) {
            gui_command_table[i].handler(client_fd);
            return;
        }
    }
    dprintf(client_fd, "Invalid command: %s", cmd);
}
