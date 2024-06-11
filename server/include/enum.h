/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef ENUM_H_
    #define ENUM_H_

enum Stone {
    food,
    linemate,
    deraumere,
    sibur,
    mendiane,
    phiras,
    thystame
};

enum Density {
    food_d = 50,
    linemate_d = 30,
    deraumere_d = 15,
    sibur_d = 10,
    mendiane_d = 10,
    phiras_d = 8,
    thystame_d = 5
};
// div by 100

enum Direction {
    N = 1, // y + 1
    E, // x + 1
    S, // y - 1
    W, // x - 1
};

    #define ABSOLUT(a) a < 0 ? (-a) : a
    #define MIN_ABS(a, b) (ABSOLUT(a)) < (ABSOLUT(b)) ? a : b
    #define CALC_X(x, width) x < 0 ? width + (x % width) - 1 : x % width
    #define CALC_Y(y, height) y < 0 ? height + (y % height) - 1 : y % height

    #define LENGTH(x1, x2, y1, y2) sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

#endif //ENUM_H_
