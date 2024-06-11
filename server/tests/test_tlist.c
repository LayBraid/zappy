/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "criterion/criterion.h"
#include "../include/time_cmds.h"
#include "../include/server.h"

// helper
static int tlist_len(client_t *client)
{
    int len = 0;
    tlist_cmd_t *tmp = client->time_cmds;
    while (tmp) {
        len++;
        tmp = tmp->next;
    }
    return len;
}

int test_func(client_t *client, void *args)
{
    (void)client;
    *(int *)args += 1;
}

Test(push, push_it)
{
    client_t *client = new_client(0, NULL, NULL);

    tlist_push(client, NULL, 0, NULL);
    tlist_push(client, NULL, 0, NULL);

    cr_assert_eq(tlist_len(client), 2);
}

Test(exec, exec_success)
{
    int test = 0;
    client_t *client = new_client(0, NULL, NULL);

    tlist_push(client, test_func, 0, &test);
    tlist_push(client, test_func, 20, &test);

    tlist_consume(client, time(NULL) + 1);
    tlist_consume(client, time(NULL) + 2);

    cr_assert_eq(tlist_len(client), 1);
    cr_assert_eq(test, 1);
}
