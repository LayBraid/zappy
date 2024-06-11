/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int right_response(client_t *client, void *args)
{
    (void)args;
    client->direction = client->direction == 4 ? 1 : client->direction + 1;
    update_player_position(client);
    return 200;
}

int client_right(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)

    tlist_push(client, right_response, 7 / client->g_data->args->freq, NULL);
    return 201;
}
