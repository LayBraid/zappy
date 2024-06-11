/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include <netinet/in.h>
    #define STONES 7

typedef struct client_s client_t;
typedef struct team_s team_t;
typedef struct egg_s egg_t;
typedef struct subscription_s subscription_t;
typedef struct incantation_s incantation_t;

typedef struct tile_s {
    client_t **clients;
    int elements[STONES];
} tile_t;

typedef struct args_s {
    int port;
    int width;
    int height;
    char **names;
    int clients_nb;
    int freq;
} args_t;

typedef struct circular_buff_s {
    char *buffer;
    char *read_head;
    char *write_head;
} circular_buff_t;

typedef struct global_data_s {
    int noegrange;
    args_t *args;
    tile_t **map;
    team_t *team_list;
    client_t *client_list;
    subscription_t *sub_gui;
    incantation_t *incantation_list;
    int egg_ids;
    int client_ids;
    char *winners;
} global_data_t;

typedef struct socket_s {
    int fd;
    struct sockaddr_in saddr;
} socket_t;

typedef struct data_socket_s {
    int parent_fd;
    int connected_fd;
    circular_buff_t *read_buff;
    socket_t sock;
} data_socket_t;

typedef struct subscription_s {
    char *metadata;
    client_t **list;
} subscription_t;

typedef int (*time_func)(client_t *client, void *args);

typedef struct tlist_cmd_s {
    long int end;
    short int exec_time;
    time_func func;
    void *args;
    struct tlist_cmd_s *next;
} tlist_cmd_t;

struct client_s {
    client_t *next;
    char *username;
    socket_t socket;
    circular_buff_t *read_buff;
    circular_buff_t *write_buff;
    data_socket_t *data_socket;
    global_data_t *g_data;
    subscription_t *subscription;
    team_t *team;
    tlist_cmd_t *time_cmds;
    long int time_spawn;
    long int time_death;
    long int time_eat;
    enum {
        UNKNOWN,
        CLIENT,
        GUI,
    } type;
    enum {
        NONE,
        WAITING_PASS,
        DISCONNECTED,
        PASV,
        PORT,
        DEAD,
    } status;
    int x;
    int y;
    int direction;
    int elements[STONES];
    int level;
    int id;
    bool incantation;
};

typedef struct egg_s {
    int id;
    int x;
    int y;
    int direction;
    struct egg_s *next;
} egg_t;

typedef struct team_s {
    int places;
    char *name;
    client_t **clients;
    struct team_s *next;
    egg_t *egg_list;
} team_t;

typedef struct server_s {
    socket_t *control_socket;
    client_t *client_list;
    global_data_t *g_data;
    fd_set readfds;
    subscription_t *sub_players;
} server_t;

typedef struct commands_s {
    char *cmd;
    int (*func)(client_t *, char **);
} commands_t;

typedef struct incantation_s {
    client_t **players;
    int level;
    struct incantation_s *next;
} incantation_t;

#endif /* STRUCT_H_ */
