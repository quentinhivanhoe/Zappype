/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** gui
*/

#ifndef GUI_H_
    #define GUI_H_
    #include <stddef.h>

typedef void (*command_handler_t)(int, char **);

typedef struct gui_command_entry_s {
    const char *key;
    command_handler_t handler;
} gui_command_entry_t;

bool is_valid_command(const char *cmd);
void dispatch_command(int client_fd, const char *cmd);

void handle_msz(int client_fd, char **cmd);
void handle_tna(int client_fd, char **cmd);
void handle_mct(int client_fd, __attribute_maybe_unused__ char **cmd);
void handle_bct(int client_fd, char **cmd);
void handle_ppo(int client_fd, char **cmd);
void handle_plv(int client_fd, char **cmd);
void handle_pin(int client_fd, char **cmd);
#endif
