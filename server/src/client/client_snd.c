/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "server.h"
#include "client.h"

static void new_client_snd(client_t *new_client)
{
    new_client->time_cmds = NULL;
    new_client->time_eat = 0;
    new_client->time_death = 0;
    new_client->time_spawn = 0;
    new_client->incantation = false;
}

client_t *new_client(int fd, global_data_t *g_data, subscription_t *sub)
{
    client_t *new_client = malloc(sizeof(client_t));
    int addr_size = sizeof(new_client->socket.saddr);
    *new_client = (client_t){0};
    if (fd > 0) new_client->socket.fd = accept(fd,
        (struct sockaddr *)&new_client->socket.saddr,
        (socklen_t *)&addr_size);
    new_client->next = NULL;
    new_client->data_socket = NULL;
    new_client->username = NULL;
    new_client->team = NULL;
    new_client->read_buff = new_circular_buff();
    new_client->write_buff = new_circular_buff();
    new_client->data_socket = NULL;
    new_client->g_data = g_data;
    new_client->subscription = sub;
    new_client->direction = N;
    new_client->level = 1;
    new_client->id = *generate_client_id();
    new_client_snd(new_client);
    return new_client;
}
