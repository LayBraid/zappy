/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int fork_response(client_t *client, void *args)
{
    (void)args;
    int len = clients_len(client->team->clients) + client->team->places + 2;

    egg_t *egg = fork_egg(client->team, client);
    client->team->clients = realloc(client->team->clients,
    sizeof(client_t *) * len);
    gui_egg_was_laid_by_client(client, egg);
    return 200;
}

int client_fork(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0);

    gui_egg_laying_by_client(client);
    tlist_push(client, fork_response, 42 / client->g_data->args->freq, NULL);
    return 201;
}
