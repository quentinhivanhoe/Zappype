/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_
    #include "client.h"
    #include "../includes/clock.h"


typedef void (*ia_cmd_handler_t)(trn_t *, char **);

typedef struct ia_cmd_s {
    const char *cmd;
    ia_cmd_handler_t handler;
    size_t delay;
} ia_cmd_t;

void dispatch_ia_command(int client_index, const char *input);

void handle_forward(trn_t *trantorian, char **args);
void handle_right(trn_t *trantorian, char **args);
void handle_left(trn_t *trantorian, char **args);
void handle_connect_nbr(trn_t *trantorian, char **args);

#endif /* !IA_H_ */
