/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "inc.h"
    #include "socket.h"
    #include "arguments.h"
    #include "circular_buff.h"
    #include "teams.h"

    #define FOR_EACH(list, func, ...) { \
    client_t *tmp = *list; \
    while (tmp) { \
        client_t *next = tmp->next;\
        int i = func(tmp __VA_OPT__(,) __VA_ARGS__); \
        if (i == 1) \
            delete_client(tmp, list); \
        tmp = next; \
    } \
}

int handle_req(client_t *list, char *rec);

void reply_client(client_t *client, int return_status);

int *generate_egg_id(void);
int *generate_client_id(void);

/* ### CIRCULAR_BUFF ### */
circular_buff_t *new_circular_buff(void);
void free_circular_buff(circular_buff_t *buff);
char *get_next_cmd(circular_buff_t *buff);
char dec_read_circle_buff(circular_buff_t *buff);

void delete_data_socket(data_socket_t *data_sock);

bool write_circular_buff(circular_buff_t *buff, char *str);

void reply_client(client_t *client, int return_status);
void gui_client_death(client_t *client);
void remove_client_from_incantation(global_data_t *g_data, int id);
void delete_subscription(subscription_t *sub, client_t *to_delete);

// 404
    #define UNKNOWN_CMD() \
        write_circular_buff(client->write_buff, \
        client->type == GUI ? "suc\n" : "ko\n");

// 400
    #define INVALID_PARAMS() \
        write_circular_buff(client->write_buff, \
        client->type == GUI ? "sbp\n" : "ko\n");

// 200
    #define SUCCESS_CMD() \
        if (client->type == CLIENT) { \
            write_circular_buff(client->write_buff, "ok\n"); \
        }

// 500
    #define ERROR_CMD() \
        if (client->type == CLIENT) { \
            write_circular_buff(client->write_buff, "ko\n"); \
        }

#endif //CLIENT_H_
