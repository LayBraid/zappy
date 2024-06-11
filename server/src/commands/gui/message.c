/*
** EPITECH PROJECT, 2023
** server
** File description:
** message
*/

#include "command.h"

void gui_message_from_server(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "smg %s", client->read_buff->buffer);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
