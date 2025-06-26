/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include "trantor.h"

typedef enum client_type_e {
    UNDEFINED,
    IA,
    GUI,
    EGG
} client_type_t;

typedef union client_data_u {
    int gui_client;
    trn_t ia_client;
} client_data_t;

typedef struct client_s {
    client_type_t type;
    client_data_t data;
    size_t id;
    struct client_s *next;
} client_t;

void add_list(client_t **list, client_type_t type, int fd, trn_t trn);
client_t *get_client_by_id(size_t id);

#endif /* !CLIENT_H_ */
