/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

const int prerequisite[7][STONES] = {
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0},
    {0, 2, 0, 1, 0, 2, 0},
    {0, 1, 1, 2, 0, 1, 0},
    {0, 1, 2, 1, 3, 0, 0},
    {0, 1, 2, 3, 0, 1, 0},
    {0, 2, 2, 2, 2, 2, 1},
};

static client_t **player_for_incantation(client_t *client)
{
    client_t **clients = client->g_data->map[client->y][client->x].clients;
    client_t **players = NULL;
    int nb = 0;
    int j = 0;

    for (int i = 0; clients[i]; i++) {
        if (clients[i]->level == client->level)
            nb++;
    }
    if (nb < (client->level - client->level % 2))
        return NULL;
    players = malloc(sizeof(client_t *) * (nb + 1));
    for (int i = 0; clients[i]; i++)
        if (clients[i]->level == client->level) {
            players[j] = clients[i];
            j++;
        }
    players[j] = NULL;
    return players;
}

static incantation_t *check_start_condition(client_t *client)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));
    client_t **players = player_for_incantation(client);
    tile_t tile = client->g_data->map[client->y][client->x];

    incantation->players = players;
    if (client->level == 8 || players == NULL) {
        if (players != NULL)
            free(players);
        free(incantation);
        return NULL;
    }
    incantation->level = client->level;
    for (int i = 0; i < STONES; i++)
        if (tile.elements[i] < prerequisite[incantation->level - 1][i]) {
            free(players);
            free(incantation);
            return NULL;
        }
    incantation->next = NULL;
    return incantation;
}

int client_incantation(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)
    incantation_t *incantation = check_start_condition(client);

    if (incantation == NULL) {
        write_circular_buff(client->write_buff, "ko\n");
        return 501;
    }
    for (int i = 0; incantation->players[i]; i++) {
        incantation->players[i]->incantation = true;
        write_circular_buff(incantation->players[i]->write_buff,
        "Elevation underway\n");
    }
    add_incantation(client->g_data, incantation);
    tlist_push(client, incantation_response,
    300 / client->g_data->args->freq, incantation);
    gui_start_incantation(client, incantation->players);
    return 201;
}
