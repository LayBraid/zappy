/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static bool en_stones(client_t *client, incantation_t *incantation)
{
    tile_t tile = client->g_data->map[client->y][client->x];

    for (int i = 0; i < STONES; i++)
        if (tile.elements[i] < prerequisite[incantation->level - 1][i])
            return false;
    return true;
}

static bool en_players(client_t *client, incantation_t *incantation)
{
    int count = 0;

    if (client->level != incantation->level)
        return false;
    for (int i = 0; incantation->players[i]; i++)
        if (incantation->players[i]->level == incantation->level)
            count++;
    if (count < (incantation->level - incantation->level % 2))
        return false;
    return true;
}

static void remove_stones(client_t *client, incantation_t *incantation)
{
    tile_t tile = client->g_data->map[client->y][client->x];

    for (int i = 0; i < STONES; i++)
        tile.elements[i] -= prerequisite[incantation->level - 1][i];
    client->g_data->map[client->y][client->x] = tile;
}

static void send_new_level(incantation_t *incantation)
{
    char *response = NULL;

    asprintf(&response, "Current level: %d\n", incantation->level + 1);
    for (int i = 0; incantation->players[i]; i++) {
        incantation->players[i]->level = incantation->level + 1;
        incantation->players[i]->incantation = false;
        write_circular_buff(incantation->players[i]->write_buff, response);
        update_player_level(incantation->players[i]);
    }
    free(response);
}

int incantation_response(client_t *client, void *args)
{
    incantation_t *incantation = (incantation_t *)args;

    if (!en_players(client, incantation) || !en_stones(client, incantation)) {
        for (int i = 0; incantation->players[i]; i++) {
            incantation->players[i]->incantation = false;
            write_circular_buff(incantation->players[i]->write_buff, "ko\n");
        }
        gui_end_incantation(client, client->x, client->y, false);
        return 501;
    }
    gui_end_incantation(client, client->x, client->y, true);
    remove_stones(client, incantation);
    send_new_level(incantation);
    char *winners = has_winner_team(client->g_data->team_list);
    client->g_data->winners = winners;
    return 202;
}
