/*
** EPITECH PROJECT, 2023
** incantation
** File description:
** description
*/

#include "command.h"

void add_incantation(global_data_t *g_data, incantation_t *inc)
{
    incantation_t *tmp = g_data->incantation_list;

    if (g_data->incantation_list == NULL) {
        g_data->incantation_list = inc;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = inc;
}

void remove_client_from_incantation(global_data_t *g_data, int id)
{
    incantation_t *tmp = g_data->incantation_list;

    for (; tmp; tmp = tmp->next)
        tmp->players = remove_client_from_list(tmp->players, id);
}
