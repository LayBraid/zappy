/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "inc.h"


bool sigint(bool set)
{
    static bool sigint = false;
    if (set)
        sigint = true;
    return sigint;
}

void sigint_handler(void)
{
    sigint(true);
    printf("SIGINT received, exiting...\n");
}
