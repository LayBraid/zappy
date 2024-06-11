/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "server.h"

global_data_t *new_data(args_t *args)
{
    global_data_t *data = malloc(sizeof(global_data_t));
    data->noegrange = 19;
    data->args = args;
    data->map = generate_map(args->width, args->height);
    data->team_list = create_teams(args);
    data->sub_gui = new_subscription("gui");
    data->incantation_list = NULL;
    data->winners = NULL;
    return data;
}

int *generate_egg_id(void)
{
    static int *id;

    if (!id) {
        id = malloc(sizeof(int));
        *id = 1;
    }
    (*id)++;
    return id;
}

int *generate_client_id(void)
{
    static int *id;

    if (!id) {
        id = malloc(sizeof(int));
        *id = 1;
    }
    (*id)++;
    return id;
}
