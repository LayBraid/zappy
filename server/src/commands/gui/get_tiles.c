/*
** EPITECH PROJECT, 2023
** server
** File description:
** get_tiles
*/

#include "command.h"

/**
 * @brief Get a tile at the given position
 *
 * @param client
 * @param args
 * @return int
 */
int gui_get_tile(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(2);

    int x = atoi(args[0]);
    int y = atoi(args[1]);
    global_data_t *data = client->g_data;

    if (x >= data->args->width || y >= data->args->height || x < 0 || y < 0)
        return 400;
    tile_t tile = data->map[y][x];
    dprintf(client->socket.fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    tile.elements[food], tile.elements[linemate], tile.elements[deraumere],
    tile.elements[sibur], tile.elements[mendiane], tile.elements[phiras],
    tile.elements[thystame]);
    return 200;
}

static int gui_get_tiles_two(client_t *client, int j)
{
    char **dup_args = malloc(sizeof(char *) * 3);

    dup_args[2] = NULL;
    for (int i = 0; i < client->g_data->args->height; i++) {
            asprintf(&dup_args[0], "%d", i);
            asprintf(&dup_args[1], "%d", j);
            int ret = gui_get_tile(client, dup_args);
            free(dup_args[0]);
            free(dup_args[1]);
            if (ret != 200)
                return ret;
    }
    free(dup_args);
    return 200;
}

/**
 * @brief Get all tiles
 *
 * @param client
 * @param args
 * @return int
 */
int gui_get_all_tiles(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(0);

    for (int j = 0; j < client->g_data->args->width; j++) {
        int ret = gui_get_tiles_two(client, j);
        if (ret != 200)
            return ret;
    }
    return 200;
}
