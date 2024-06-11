/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "subscription.h"

subscription_t *new_subscription(char *metadata)
{
    subscription_t *new_sub = malloc(sizeof(subscription_t));

    new_sub->metadata = metadata;
    new_sub->list = malloc(sizeof(client_t) * SUB_SIZE);
    for (int i = 0; i < SUB_SIZE; i++) {
        new_sub->list[i] = NULL;
    }
    return new_sub;
}

void subscribe(subscription_t *sub, client_t **new_sub)
{
    int i = 0;
    for (; sub->list[i] && i < SUB_SIZE; i++);
    if (i == SUB_SIZE)
        return;
    sub->list[i] = *new_sub;
}

void delete_subscription(subscription_t *sub, client_t *to_delete)
{
    for (int i = 0; sub->list && i < SUB_SIZE; i++) {
        if (sub->list[i] == to_delete)
            sub->list[i] = NULL;
    }
}

void broadcast(subscription_t *sub, char *msg)
{
    if (sub->list == NULL)
        return;
    for (int i = 0; i < SUB_SIZE; i++) {
        if (sub->list[i] != NULL) {
            printf("Broadcasting to %s\n", sub->list[i]->username);
            write_circular_buff(sub->list[i]->write_buff, msg);
            write_circular_buff(sub->list[i]->write_buff, "\n");
        }
    }
}
