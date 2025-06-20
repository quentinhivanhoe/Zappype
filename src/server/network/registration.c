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

static size_t count_clients_per_team(char *name)
{
    if (strcmp(name, "GRAPHIC") == 0)
        return count_gui_clients();
    for (size_t i = 0; i < my_server()->params.team_nbr; i++) {
        if (strcmp(name, my_server()->params.team_names[i]) == 0) {
            return count_ia_clients(i);
        }
    }
    return 0;
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

void process_ia_connection(int i, int team_index)
{
    trn_t *trantorian = &my_server()->info.clients[i].data.ia_client;
    ssize_t free_slots = (ssize_t)my_server()->params.cli_per_team
    - ((ssize_t)count_ia_clients(team_index) + 1);

    init_trantorian(trantorian, i, team_index);
    dprintf(trantorian->socket, "%lu\n", (free_slots <= 0) ? 0 : free_slots);
    dprintf(trantorian->socket, "%ld %ld\n", my_server()->params.width,
        my_server()->params.height);
}

void register_ia_client(int i, char *team_name)
{
    int team_index = -1;

    for (int j = 0; j < (int)my_server()->params.team_nbr - 1; j++) {
        if (strcmp(team_name, my_server()->params.team_names[j]) == 0) {
            team_index = j;
            break;
        }
    }
    if (team_index < 0) {
        dprintf(my_server()->info.fds[i].fd, "'%s': not found.\n", team_name);
        remove_client(i);
        return;
    }
    if (count_clients_per_team(team_name) >= my_server()->params.cli_per_team){
        dprintf(my_server()->info.fds[i].fd,
            "Team '%s' is full.\n", team_name);
        remove_client(i);
        return;
    }
    process_ia_connection(i, team_index);
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
