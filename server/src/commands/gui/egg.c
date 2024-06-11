/*
** EPITECH PROJECT, 2023
** server
** File description:
** egg
*/

#include "command.h"

void gui_egg_laying_by_client(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "pfk %d", client->id);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void gui_egg_was_laid_by_client(client_t *client, egg_t *egg)
{
    char *response = NULL;

    asprintf(&response, "enw %d %d %d %d\n", egg->id, client->id,
        egg->x, egg->y);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void gui_egg_death(client_t *client, egg_t *egg)
{
    char *response = NULL;

    asprintf(&response, "edi %d", egg->id);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
