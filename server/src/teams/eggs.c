/*
** EPITECH PROJECT, 2023
** teams
** File description:
** description
*/

#include "teams.h"

egg_t *new_egg(int width, int height)
{
    egg_t *new = malloc(sizeof(egg_t));

    if (new == NULL)
        return NULL;
    new->id = *generate_egg_id();
    new->x = rand() % width;
    new->y = rand() % height;
    new->direction = rand() % 4 + 1;
    new->next = NULL;
    return new;
}

static egg_t *layed_egg(int x, int y, int direction)
{
    egg_t *new = malloc(sizeof(egg_t));

    if (new == NULL)
        return NULL;
    new->id = *generate_egg_id();
    new->x = x;
    new->y = y;
    new->direction = direction;
    new->next = NULL;
    return new;
}

egg_t *add_egg(team_t *team, args_t *args)
{
    egg_t *new = new_egg(args->width, args->height);
    egg_t *tmp = team->egg_list;

    team->places++;
    if (team->egg_list == NULL) {
        team->egg_list = new;
        return new;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return new;
}

egg_t *create_eggs(args_t *args)
{
    egg_t *head = new_egg(args->width, args->height);
    egg_t *tmp = head;

    for (int i = 1; i < args->clients_nb; i++) {
        tmp->next = new_egg(args->width, args->height);
        tmp = tmp->next;
    }
    return head;
}

egg_t *fork_egg(team_t *team, client_t *client)
{
    egg_t *new = layed_egg(client->x, client->y, client->direction);
    egg_t *tmp = team->egg_list;

    team->places++;
    if (team->egg_list == NULL) {
        team->egg_list = new;
        return new;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return new;
}
