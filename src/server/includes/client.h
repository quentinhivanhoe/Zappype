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
    GUI
} client_type_t;

typedef union client_data_u {
    int gui_client;
    trn_t ia_client;
} client_data_t;

typedef struct client_s {
    client_type_t type;
    client_data_t data;
} client_t;

#endif /* !CLIENT_H_ */
