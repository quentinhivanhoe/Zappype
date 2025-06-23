/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** registration
*/

#include "../includes/server.h"

static size_t count_gui_clients(void)
{
    size_t count = 0;

    for (size_t i = 0; i < my_server()->params.max_clients; i++) {
        if (my_server()->info.clients[i].type == GUI) {
            count++;
        }
    }
    return count;
}

size_t count_ia_clients(size_t id)
{
    size_t count = 0;

    for (size_t j = 0; j < my_server()->params.max_clients; j++) {
        if (my_server()->info.clients[j].type == IA &&
            my_server()->info.clients[j].data.ia_client.team_id == id) {
            count++;
        }
    }
    return count;
}

void register_gui_client(int i)
{
    if (count_gui_clients() >= my_server()->params.cli_per_team) {
        dprintf(my_server()->info.fds[i].fd,
            "Maximum number of GUI clients reached.\n");
        remove_client(i);
        return;
    }
    my_server()->info.clients[i].data.gui_client = my_server()->info.fds[i].fd;
    dprintf(2,
        "You are now registered as a GUI client.\n");
    dprintf(my_server()->info.clients[i].data.gui_client, "ok\n");
    my_server()->info.clients[i].type = GUI;
    return;
}

void process_ia_connection(client_t *clients, int i, size_t team_index)
{
    team_t t = {0};

    for (size_t n = 0; n < my_server()->params.max_clients; n++) {
        if (clients[n].type != EGG)
            continue;
        if (clients[n].data.ia_client.team_id != team_index)
            continue;
        clients[n].type = IA;
        clients[n].data.ia_client.socket = my_server()->info.fds[i].fd;
        my_server()->info.fds[n] = my_server()->info.fds[i];
        my_server()->info.fds[i].fd = -1;
        my_server()->params.teams[team_index].trn_count++;
        my_server()->params.teams[team_index].egg_count--;
        ebo_command(n);
        t = my_server()->params.teams[team_index];
        dprintf(my_server()->info.fds[n].fd, "%ld\n", t.max - t.trn_count);
        dprintf(my_server()->info.fds[n].fd, "%ld %ld\n",
        my_server()->params.width, my_server()->params.height);
        break;
    }
}

void register_ia_client(int i, char *team_name)
{
    int team_index = -1;

    for (int j = 0; j < (int)my_server()->params.team_nbr - 1; j++) {
        if (strcmp(team_name, my_server()->params.teams[j].name) == 0) {
            team_index = j;
            break;
        }
    }
    if (team_index < 0) {
        dprintf(my_server()->info.fds[i].fd, "'%s': not found.\n", team_name);
        remove_client(i);
        return;
    }
    if (my_server()->params.teams[team_index].egg_count) {
        my_server()->info.trn_count++;
        return process_ia_connection(my_server()->info.clients, i, team_index);
    }
    dprintf(my_server()->info.fds[i].fd, "No slots for '%s'\n", team_name);
    remove_client(i);
}

void det_teams(char *buffer, int i)
{
    char *team_name = strtok(buffer, "\n");

    if (team_name == NULL || strlen(team_name) == 0) {
        dprintf(my_server()->info.fds[i].fd, "Invalid team name.\n");
        remove_client(i);
        return;
    }
    if (strcmp(team_name, "GRAPHIC") == 0)
        return register_gui_client(i);
    return register_ia_client(i, team_name);
}
