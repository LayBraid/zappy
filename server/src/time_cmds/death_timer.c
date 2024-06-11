/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "time_cmds.h"

int eat_timer(client_t *client)
{
    if (client->type != CLIENT)
        return 0;
    if (client->time_eat != 0 && time(NULL) >= client->time_eat)
        client->time_eat = 0;
    if (client->time_eat == 0 && client->elements[0] != 0) {
        client->elements[0]--;
        client->time_death += 126;
    }
    return 0;
}

int death_timer(client_t *client)
{
    if (client->type != CLIENT)
        return 0;
    if (client->elements[0] == 0 && time(NULL) >= client->time_spawn +
    client->time_death / client->g_data->args->freq) {
        client->status = DISCONNECTED;
    }
    return 0;
}
