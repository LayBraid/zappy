/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int client_connect_nbr(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(1)
    char *response = NULL;

    asprintf(&response, "%d\n", client->team->places);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}
