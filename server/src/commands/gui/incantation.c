/*
** EPITECH PROJECT, 2023
** server
** File description:
** incantation
*/

#include "command.h"

void gui_start_incantation(client_t *client, client_t **clients)
{
    char *response = NULL;
    char *tmp = NULL;

    asprintf(&response, "pic %d %d %d", client->x, client->y, client->level);
    for (int i = 0; clients[i]; i++) {
        tmp = response;
        asprintf(&response, "%s %d", response, clients[i]->id);
        free(tmp);
    }
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void gui_end_incantation(client_t *client, int x, int y, bool result)
{
    char *response = NULL;

    asprintf(&response, "pie %d %d %s", x, y, result == true ? "ok" : "ko");
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
