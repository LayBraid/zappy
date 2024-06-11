/*
** EPITECH PROJECT, 2023
** server
** File description:
** update_gui
*/

#include "command.h"

void update_player_level(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "plv %d %d", client->id, client->level);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void update_player_inventory(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "pin %d %d %d %d %d %d %d %d %d %d", client->id, \
    client->x,
    client->y, client->elements[food], client->elements[linemate],
    client->elements[deraumere], client->elements[sibur],
    client->elements[mendiane], client->elements[phiras],
    client->elements[thystame]);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void update_player_position(client_t *client)
{
    char *response = NULL;

    asprintf(&response, "ppo %d %d %d %d", client->id, client->x, client->y, \
    client->direction);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void update_tile(client_t *client, int x, int y)
{
    char *response = NULL;

    tile_t tile = client->g_data->map[y][x];
    asprintf(&response, "bct %d %d %d %d %d %d %d %d %d", x, y,
    tile.elements[food], tile.elements[linemate], tile.elements[deraumere],
    tile.elements[sibur], tile.elements[mendiane], tile.elements[phiras],
    tile.elements[thystame]);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

void update_tile_gdata(global_data_t *gdata, int x, int y)
{
    char *response = NULL;

    tile_t tile = gdata->map[y][x];
    asprintf(&response, "bct %d %d %d %d %d %d %d %d %d", x, y,
    tile.elements[food], tile.elements[linemate], tile.elements[deraumere],
    tile.elements[sibur], tile.elements[mendiane], tile.elements[phiras],
    tile.elements[thystame]);
    broadcast(gdata->sub_gui, response);
    free(response);
}
