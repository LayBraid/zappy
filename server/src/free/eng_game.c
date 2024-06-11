/*
** EPITECH PROJECT, 2023
** server
** File description:
** eng_game
*/

#include "command.h"

void free_egg(egg_t *egg)
{
    for (egg_t *tmp = egg; tmp; ) {
        tmp = tmp->next;
        free(egg);
        egg = tmp;
    }
}

void free_team(team_t *team)
{
    for (team_t *tmp = team; tmp; ) {
        tmp = tmp->next;
        free(team->clients);
        free_egg(team->egg_list);
        free(team);
        team = tmp;
    }
}

void free_incantation(incantation_t *incantation)
{
    for (incantation_t *tmp = incantation; tmp; ) {
        tmp = tmp->next;
        free(incantation->players);
        free(incantation);
        incantation = tmp;
    }
}

void free_map(tile_t **map, int x, int y)
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            free(map[i][j].clients);
        }
        free(map[i]);
    }
    free(map);
}

void close_game(server_t *serv)
{
    int *client_id = generate_client_id();
    int *egg_id = generate_egg_id();

    gui_end_game(serv->g_data, serv->g_data->winners);
    free_incantation(serv->g_data->incantation_list);
    free_tab(serv->g_data->args->names);
    free_team(serv->g_data->team_list);
    free_map(serv->g_data->map, serv->g_data->args->width,
    serv->g_data->args->height);
    free(serv->g_data->args);
    free(serv->g_data->sub_gui->list);
    free(serv->g_data->sub_gui);
    free(serv->sub_players->list);
    free(serv->sub_players);
    free(serv->g_data);
    free(client_id);
    free(egg_id);
}
