/*
** EPITECH PROJECT, 2023
** teams
** File description:
** description
*/

#include "teams.h"

static team_t *new_team(args_t *args, char *name, int clients_nb)
{
    team_t *new = malloc(sizeof(team_t));

    if (new == NULL)
        return NULL;
    new->places = clients_nb;
    new->name = name;
    new->egg_list = create_eggs(args);
    new->clients = malloc(sizeof(client_t *) * (clients_nb + 1));
    new->clients[0] = NULL;
    new->next = NULL;
    return new;
}

team_t *create_teams(args_t *args)
{
    team_t *head = new_team(args, args->names[0], args->clients_nb);
    team_t *tmp = head;

    for (int i = 1; args->names[i]; i++) {
        tmp->next = new_team(args, args->names[i], args->clients_nb);
        tmp = tmp->next;
    }
    return head;
}

team_t *find_team(team_t *team, char *name)
{
    for (team_t *tmp = team; tmp != NULL; tmp = tmp->next)
        if (strcmp(name, tmp->name) == 0)
            return tmp;
    return NULL;
}

static void check_level(team_t *tmp, int i, int *nb_max_lvl)
{
    if (tmp->clients[i]->level >= 8)
        (*nb_max_lvl)++;
}

char *has_winner_team(team_t *teams)
{
    team_t *tmp = teams;

    while (tmp) {
        int nb_max_lvl = 0;
        for (int i = 0; tmp->clients[i]; i++)
            check_level(tmp, i, &nb_max_lvl);
        if (nb_max_lvl >= 6)
            return tmp->name;
        tmp = tmp->next;
    }
    return NULL;
}
