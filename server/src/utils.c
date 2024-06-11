/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "inc.h"

int occurence(char *str, char c)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            count++;
        i++;
    }
    return count;
}

int tab_len(char **tab)
{
    int i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

void remove_trailing(char *str)
{
    if (*str == '\0')
        return;
    if (*str == '\r' || *str == '\n')
        *str = '\0';
    remove_trailing(str + 1);
}

char **str_split(char *str, char c)
{
    char **tab = malloc(sizeof(char *) * (occurence(str, c) + 2));
    char *token = strtok(str, &c);
    int i = 0;

    while (token) {
        tab[i] = strdup(token);
        tab[i][strlen(tab[i])] = '\0';
        token = strtok(NULL, &c);
        i++;
    }
    tab[i] = NULL;
    return tab;
}
