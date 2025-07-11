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
int get_object_index(const char *name);

void handle_forward(trn_t *trantorian, char **args);
void handle_right(trn_t *trantorian, char **args);
void handle_left(trn_t *trantorian, char **args);
void handle_connect_nbr(trn_t *trantorian, char **args);
void handle_inventory(trn_t *trantorian, char **args);
void handle_look(trn_t *trantorian, char **args);
void handle_take(trn_t *trantorian, char **args);
void handle_set(trn_t *trantorian, char **args);
void handle_incantation(trn_t *trantorian, char **args);
void handle_eject(trn_t *trantorian, char **args);
void handle_broadcast(trn_t *trantorian, char **args);
void handle_fork(trn_t *trn, char **args);

#endif /* !IA_H_ */
