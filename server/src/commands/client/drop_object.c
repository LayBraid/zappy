/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int drop_object_callback(client_t *client, void *args)
{
    int *stone_index = (int *) args;

    gui_drop_object(client, *stone_index);
    update_tile(client, client->x, client->y);
    update_player_inventory(client);
    return 200;
}

int client_drop_object(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(1)
    int stone_index = find_stone(client->elements, args[0]);
    int *s_index = NULL;

    if (stone_index == -1)
        return 400;
    client->elements[stone_index]--;
    client->g_data->map[client->y][client->x].elements[stone_index]++;
    s_index = malloc(sizeof(int));
    *s_index = stone_index;
    tlist_push(client, drop_object_callback, 7 / client->g_data->args->freq,
    s_index);
    return 201;
}
