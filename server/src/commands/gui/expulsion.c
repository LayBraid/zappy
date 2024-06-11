/*
** EPITECH PROJECT, 2023
** server
** File description:
** expulsion
*/

#include "command.h"

void gui_expulsion(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "pex %d", client->id);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
