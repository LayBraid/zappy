/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "time_cmds.h"

static int tlist_len(client_t *client)
{
    int len = 0;
    tlist_cmd_t *tmp = client->time_cmds;
    while (tmp) {
        len++;
        tmp = tmp->next;
    }
    return len;
}

void tlist_push(client_t *client, time_func func, short int timout, void *args)
{
    if (tlist_len(client) >= 11)
        return;

    tlist_cmd_t *new = malloc(sizeof(tlist_cmd_t));
    new->func = func;
    new->exec_time = timout;
    new->args = args;
    new->next = NULL;
    if (client->time_cmds == NULL) {
        new->end = time(NULL) + timout;
        client->time_cmds = new;
        return;
    }
    tlist_cmd_t *tmp = client->time_cmds;
    while (tmp->next) {
        tmp = tmp->next;
    }

    tmp->next = new;
}

int tlist_consume(client_t *client, int now)
{
    if (client->time_cmds == NULL) {
        return 0;
    }
    tlist_cmd_t *tmp = client->time_cmds;
    if (tmp->end < now) {
        int return_status = tmp->func(client, tmp->args);
        reply_client(client, return_status);
        client->time_cmds = tmp->next;
        if (client->time_cmds)
            client->time_cmds->end = time(NULL) + client->time_cmds->exec_time;
        free(tmp);
        return 0;
    }

    return 0;
}
