/*
** EPITECH PROJECT, 2023
** server
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

    #include <getopt.h>
    #include <stdlib.h>
    #include "inc.h"

extern int tab_len(char **tab);

args_t *parse_args(int ac, char **av);

#endif /* !ARGUMENTS_H_ */
