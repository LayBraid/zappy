/*
** EPITECH PROJECT, 2023
** server
** File description:
** end_game
*/

#include "command.h"

void gui_end_game(global_data_t *g_data, char *winner_name)
{
    char *response = NULL;

    asprintf(&response, "seg %s", winner_name);
    broadcast(g_data->sub_gui, response);
    free(response);
}
