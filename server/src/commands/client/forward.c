/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int sanmove_x(int x, int width, int direction)
{
    if (direction == E)
        return x != width - 1 ? x + 1 : 0;
    if (direction == W)
        return x != 0 ? x - 1 : width - 1;
    return x;
}

int sanmove_y(int y, int heightn, int direction)
{
    if (direction == N)
        return y != 0 ? y - 1 : heightn - 1;
    if (direction == S)
        return y != heightn - 1 ? y + 1 : 0;
    return y;
}

static int forward_response(client_t *client, void *args)
{
    (void)args;

    int x = sanmove_x(client->x, client->g_data->args->width, \
    client->direction);
    int y = sanmove_y(client->y, client->g_data->args->height, \
    client->direction);

    moov_player(client, x, y);
    client->x = x;
    client->y = y;
    update_player_position(client);
    return 200;
}

int client_forward(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)

    tlist_push(client, forward_response, 7 / client->g_data->args->freq, NULL);
    return 201;
}
