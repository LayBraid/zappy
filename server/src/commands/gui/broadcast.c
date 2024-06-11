/*
** EPITECH PROJECT, 2023
** server
** File description:
** broadcast
*/

#include "command.h"

void gui_broadcast(client_t *client, char *msg)
{
    char *response = NULL;

    asprintf(&response, "pbc %d %s", client->id, msg);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
