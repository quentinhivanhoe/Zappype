/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** server
*/

#ifndef HANDLE_GUI_H_
    #define HANDLE_GUI_H_
    #include <stddef.h>

typedef void (*command_handler_t)(int);

typedef struct gui_command_entry_s{
    const char *key;
    command_handler_t handler;
} gui_command_entry_t;

bool is_valid_command(const char *cmd);
void dispatch_command(int client_fd, const char *cmd);

void handle_msz(int client_fd);
void handle_mct(int client_fd);
void handle_bct(int client_fd);
void handle_ppo(int client_fd);
void handle_spn(int client_fd);
void handle_spp(int client_fd);

#endif