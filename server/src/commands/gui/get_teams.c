/*
** EPITECH PROJECT, 2023
** server
** File description:
** get_teams
*/

#include "command.h"

/**
 * @brief Get all the teams
 *
 * @param client
 * @param args
 * @return int
 */
int gui_get_teams(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(0);
    char *response = NULL;

    for (int i = 0; client->g_data->args->names[i]; i++) {
        asprintf(&response, "tna %s\n", client->g_data->args->names[i]);
        write_circular_buff(client->write_buff, response);
        free(response);
    }
    return 200;
}
