/*
** EPITECH PROJECT, 2023
** server
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "inc.h"

tile_t **generate_map(int width, int height);
void delete_map(tile_t **map, int height);
void generate_ressources(tile_t **map, int width, int height);
void refill_ressources(global_data_t *gdata);
void refill(global_data_t *gdata);

extern void update_tile_gdata(global_data_t *gdata, int x, int y);

#endif /* !MAP_H_ */
