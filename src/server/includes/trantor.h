/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** trantor
*/

#ifndef TRANTOR_H_
    #define TRANTOR_H_
    #include <stdint.h>
    #include <unistd.h>
    #define OBJECT_DEFINED 7
    #define MAX_REQUEST 10

typedef uint64_t obj_t;
typedef struct trantorian_s trn_t;

typedef enum object_index_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} obj_idx_t;


typedef enum direction_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
} dir_t;

typedef enum trantorian_status_e {
    ALIVE,
    DEAD,
    FROZEN
} trn_stat_t;

typedef struct position_s {
    uint64_t x;
    uint64_t y;
    dir_t dir;
} pos_t;

typedef void (*req_func_t)(trn_t *, char **);

typedef struct req_queue_s {
    req_func_t callback;
    size_t delay;
    char **args;
} req_queue_t;

struct trantorian_s {
    pos_t pos;
    uint8_t lvl;
    size_t team_id;
    uint8_t req_count;
    trn_stat_t stat;
    obj_t inventory[OBJECT_DEFINED];
    req_queue_t req_queue[MAX_REQUEST];
    size_t frame_count;
    int socket;
};

typedef struct tile_s tile_t;

typedef struct tile_s {
    obj_t content[OBJECT_DEFINED];
} tile_t;

tile_t get_object(tile_t *tile, ssize_t x, ssize_t y);
size_t get_trantorian_index(trn_t *trantorian);

extern const float density_table[OBJECT_DEFINED + 1];

tile_t *init_map(size_t len_map);
void parse_req(void);
void add_req(trn_t *trn, char **args, req_func_t func, size_t delay);

#endif /* !TRANTOR_H_ */
