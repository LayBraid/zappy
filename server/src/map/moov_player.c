/*
** EPITECH PROJECT, 2023
** server
** File description:
** map
*/

#include "map.h"

int clients_len(client_t **clients)
{
    int len = 0;

    while (clients[len])
        len++;
    return len;
}

client_t **remove_client_from_list(client_t **clients, int id)
{
    client_t **new_list = malloc(sizeof(client_t *) * clients_len(clients));
    int j = 0;

    for (int i = 0; clients[i]; i++) {
        if (clients[i]->id != id) {
            new_list[j] = clients[i];
            j++;
        }
    }
    new_list[j] = NULL;
    free(clients);
    return new_list;
}

client_t **add_client_to_list(client_t **clients, client_t *client)
{
    client_t **new_list =
    malloc(sizeof(client_t *) * (clients_len(clients) + 2));
    int j = 0;

    for (int i = 0; clients[i]; i++, j++)
        new_list[j] = clients[i];
    new_list[j] = client;
    new_list[j + 1] = NULL;
    free(clients);
    return new_list;
}

void moov_player(client_t *client, int x, int y)
{
    tile_t *bef_tile = &client->g_data->map[client->y][client->x];
    tile_t *aft_tile = &client->g_data->map[y][x];

    bef_tile->clients = remove_client_from_list(bef_tile->clients, client->id);
    aft_tile->clients = add_client_to_list(aft_tile->clients, client);
}
