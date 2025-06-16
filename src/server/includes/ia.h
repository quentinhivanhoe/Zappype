/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** ia
*/

#ifndef IA_H_
    #define IA_H_
    #include "client.h"


typedef void (*ia_cmd_handler_t)(trn_t *trantorian, char **args);

typedef struct ia_cmd_s {
    const char *cmd;
    ia_cmd_handler_t handler;
    size_t delay;
} ia_cmd_t;

void dispatch_ia_command(int client_index, const char *input);

void handle_forward(__attribute_maybe_unused__ trn_t *trantorian,__attribute_maybe_unused__ char **args);
#endif /* !IA_H_ */
