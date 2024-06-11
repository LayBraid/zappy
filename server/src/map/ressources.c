/*
** EPITECH PROJECT, 2023
** server
** File description:
** ressources
*/

#include "map.h"

const float density[STONES] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};

void generate_ressources(tile_t **map, int width, int height)
{
    for (int k = 0; k < STONES; k++) {
        for (int i = 0; (float)i < density[k] * (float)width * \
        (float)height; i++) {
            int x = (int)rand() % width;
            int y = (int)rand() % height;
            map[y][x].elements[k]++;
        }
    }
}

int get_current_occurence(tile_t **map, int width, int height, int stone)
{
    int occurence = 0;

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            occurence += map[y][x].elements[stone];
    return occurence;
}

void refill_ressources(global_data_t *gdata)
{
    int width = gdata->args->width;
    int height = gdata->args->height;

    for (int k = 0; k < STONES; k++) {
        int occurence = get_current_occurence(gdata->map, width, height, k);
        for (int i = 0; (float)i + (float)occurence <
                density[k] *(float)width * (float)height; i++) {
            int x = (int)rand() % width;
            int y = (int)rand() % height;
            gdata->map[y][x].elements[k]++;
            update_tile_gdata(gdata, x, y);
        }
    }
}
