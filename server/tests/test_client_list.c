/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "criterion/criterion.h"
#include "../include/client.h"
#include "../include/server.h"

void push(client_t **list, client_t *new_sock);

Test(push, push_on_null)
{
    client_t *list = NULL;
    client_t *new = new_client(0, NULL, NULL);

    strcpy(new->read_buff->buffer, "salut");

    push(&list, new);
    cr_assert_eq(strcmp(list->read_buff->buffer, "salut"), 0);
}

Test(push, push_normal)
{
    char *tests[4] = {"salut", "au revoir", "adieu", ""};

    client_t *list = NULL;
    client_t *n1 = new_client(0, NULL, NULL);
    strcpy(n1->read_buff->buffer, "salut");

    client_t *n2 = new_client(0, NULL, NULL);
    strcpy(n2->read_buff->buffer, "au revoir");

    client_t *n3 = new_client(0, NULL, NULL);
    strcpy(n3->read_buff->buffer, "adieu");

    client_t *n4 = new_client(0, NULL, NULL);
    strcpy(n4->read_buff->buffer, "");

    push(&list, n1);
    push(&list, n2);
    push(&list, n3);
    push(&list, n4);

    cr_assert_eq(strcmp(list->read_buff->buffer, tests[0]), 0);
    for (int i = 1; i < 4; i++) {
        list = list->next;
        cr_assert_eq(strcmp(list->read_buff->buffer, tests[i]), 0);
    }
}

Test(delete, delete_on_null)
{
    client_t *list = NULL;
    client_t *new = new_client(0, NULL, NULL);
    strcpy(new->read_buff->buffer, "salut");

    delete(&list, new);
    cr_assert_eq(list, NULL);
}

Test(delete, delete_normal)
{
    char *tests[4] = {"salut", "au revoir", "adieu", ""};

    client_t *list = NULL;
    client_t *n1 = new_client(0, NULL, NULL);
    strcpy(n1->read_buff->buffer, "salut");

    client_t *n2 = new_client(0, NULL, NULL);
    strcpy(n2->read_buff->buffer, "au revoir");

    client_t *n3 = new_client(0, NULL, NULL);
    strcpy(n3->read_buff->buffer, "adieu");

    client_t *n4 = new_client(0, NULL, NULL);
    strcpy(n4->read_buff->buffer, "");

    push(&list, n1);
    push(&list, n2);
    push(&list, n3);
    push(&list, n4);

    delete(n2, &list);
    list = list->next;
    cr_assert_eq(strcmp(list->read_buff->buffer, tests[2]), 0);
}
