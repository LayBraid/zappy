/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int vector_calc(int a, int b, int max)
{
    if (a < b)
        return MIN_ABS((b - a), (b - max - a));
    return MIN_ABS((b - a), (max - a + b));
}

int sound_tile_calc(int a, bool left)
{
    int tile = a < 45 ? 1 : a == 45 ? 2 : a > 45 && a < 135 ? 3 : 0;

    if (a >= 135)
        tile = a == 135 ? 4 : 5;
    if (left || tile == 1)
        return tile;
    return 10 - tile;
}
