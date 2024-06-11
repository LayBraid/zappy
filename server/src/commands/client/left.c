/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int left_response(client_t *client, void *args)
{
    (void)args;
    client->direction = client->direction - 1 == 0 ? 4 : client->direction - 1;
    update_player_position(client);
    return 200;
}

int client_left(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)

    tlist_push(client, left_response, 7 / client->g_data->args->freq, NULL);
    return 201;
}
