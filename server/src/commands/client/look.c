/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

const char inventory_names[7][10] = {"food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame"};

static void on_tile(client_t *client, tile_t tile)
{
    for (int i = 0; tile.clients[i]; i++)
        write_circular_buff(client->write_buff, " player");
    for (int i = 0; i < STONES; i++) {
        for (int j = 0; j < tile.elements[i]; j++) {
            write_circular_buff(client->write_buff, " ");
            write_circular_buff(client->write_buff,
            (char *)inventory_names[i]);
        }
    }
}

static void look_range(client_t *client)
{
    write_circular_buff(client->write_buff, "[");
    for (int i = 0; i <= client->level; i++) {
        for (int j = 0; j < 1 + i * 2; j++) {
            write_circular_buff(client->write_buff,
            i == 0 && j == 0 ? "" : ",");
            on_tile(client, client->g_data->map[look_y(client, i,
            j)][look_x(client, i, j)]);
        }
    }
    write_circular_buff(client->write_buff, "]\n");
}

static int look_reponse(client_t *client, void *args)
{
    (void)args;
    look_range(client);
    return 202;
}

int client_look(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)

    tlist_push(client, look_reponse, 7 / client->g_data->args->freq, NULL);
    return 201;
}
