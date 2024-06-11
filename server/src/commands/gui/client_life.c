/*
** EPITECH PROJECT, 2023
** server
** File description:
** client_connect
*/

#include "command.h"

void gui_new_connection(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "pnw %d %d %d %d %d %s", client->id, client->x, \
    client->y, client->direction, client->level, client->team->name);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void gui_client_connection_for_an_egg(client_t *client, int egg_id)
{
    char *response = NULL;

    asprintf(&response, "ebo %d", egg_id);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void gui_client_death(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "pdi %d", client->id);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
