/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_size
*/

#include "command.h"

/**
 * @brief Get the size of the map
 *
 * @param client
 * @param args
 * @return int
 */
int gui_map_size(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(0);
    char *response = NULL;

    asprintf(&response, "msz %d %d\n", client->g_data->args->width, \
    client->g_data->args->height);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}
