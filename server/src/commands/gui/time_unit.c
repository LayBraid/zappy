/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** time_unit
*/

#include "command.h"

int gui_get_time_unit(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(0);

    char *response = NULL;

    asprintf(&response, "sgt %d\n", client->g_data->args->freq);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}

int gui_set_time_unit(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(1);

    char *response = NULL;
    int new_time_unit = atoi(args[0]);
    client->g_data->args->freq = new_time_unit;
    asprintf(&response, "sst %d\n", new_time_unit);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}
