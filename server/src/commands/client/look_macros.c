/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int look_x(client_t *client, int i, int j)
{
    int width = client->g_data->args->width;

    if (client->direction == N)
        return CALC_X((client->x - i + j), width);
    if (client->direction == E)
        return CALC_X((client->x + i), width);
    if (client->direction == S)
        return CALC_X((client->x + i - j), width);
    return CALC_X((client->x - i), width);
}

int look_y(client_t *client, int i, int j)
{
    int height = client->g_data->args->height;

    if (client->direction == N)
        return CALC_Y((client->y - i), height);
    if (client->direction == E)
        return CALC_Y((client->y - i + j), height);
    if (client->direction == S)
        return CALC_Y((client->y + i), height);
    return CALC_Y((client->y + i - j), height);
}
