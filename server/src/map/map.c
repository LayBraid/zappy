/*
** EPITECH PROJECT, 2023
** server
** File description:
** map
*/

#include "map.h"

tile_t new_tile(void)
{
    tile_t new = {NULL, {0, 0, 0, 0, 0, 0, 0}};

    new.clients = malloc(sizeof(client_t *));
    new.clients[0] = NULL;
    return new;
}

tile_t *generate_row(int width)
{
    tile_t *row = malloc(sizeof(tile_t) * (width));

    for (int i = 0; i < width; i++)
        row[i] = new_tile();
    return row;
}

tile_t **generate_map(int width, int height)
{
    tile_t **map = malloc(sizeof(tile_t *) * (height));

    for (int i = 0; i < height; i++)
        map[i] = generate_row(width);
    generate_ressources(map, width, height);
    return map;
}

void delete_map(tile_t **map, int height)
{
    if (map == NULL)
        return;
    for (int i = 0; i < height; i++)
        free(map[i]);
    free(map);
}

void refill(global_data_t *gdata)
{
    static time_t last = 0;
    if (time(NULL) - last < 20 / gdata->args->freq)
        return;

    last = time(NULL);
    refill_ressources(gdata);
}
