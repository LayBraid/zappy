/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static void eject_player(client_t *client, char *response)
{
    int x = sanmove_x(client->x, client->direction, \
    client->g_data->args->width);
    int y = sanmove_y(client->y, client->direction, \
    client->g_data->args->height);

    moov_player(client, x, y);
    client->x = x;
    client->y = y;
    write_circular_buff(client->write_buff, response);
    gui_expulsion(client);
    update_player_position(client);
}

static int eject_response(client_t *client, void *args)
{
    (void)args;
    char *response = NULL;
    int direction = client->direction == N ? S : client->direction == S ? \
    N : client->direction == E ? W : E;
    client_t **clients = client->g_data->map[client->y][client->x].clients;

    asprintf(&response, "eject: %d\n", direction);
    for (int i = 0; clients[i]; i++) {
        if (client->id != clients[i]->id)
            eject_player(clients[i], response);
    }
    free(response);
    return 200;
}

int client_eject(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)

    tlist_push(client, eject_response, 7 / client->g_data->args->freq, NULL);
    return 201;
}
