/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "client.h"
    #include "arguments.h"
    #include "command.h"
    #include "teams.h"
    #include "subscription.h"
    #include "map.h"

socket_t *new_control_socket(int connection_port);
client_t *new_client(int fd, global_data_t *g_data, subscription_t *sub);
int delete_client(client_t *to_delete, client_t **list);
client_t *get_client(client_t **list, int fd);

void push(client_t **list, client_t *new_sock);
/* ### CLIENT METHODS ### */
int set_fd(client_t *client, fd_set *readfds, int *max_fd);
int check_read_fd(client_t *client, fd_set *readfds);
int handle_commands(client_t *client);
int write_needed(client_t *client);
int death_timer(client_t *client);
int eat_timer(client_t *client);

int check_disconnect(client_t *client);

global_data_t *new_data(args_t *args);

int get_number_of_connected_players(global_data_t *g_data);

int tlist_consume(client_t *client, int now);

bool sigint(bool set);

#endif //SERVER_H_
