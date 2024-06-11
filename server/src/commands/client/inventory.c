/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int in_inventory(client_t *client, void *args)
{
    (void)args;
    char *str = NULL;
    char *tmp = NULL;

    asprintf(&tmp, "[food %d", client->elements[0]);
    for (int i = 1; i < STONES; i++) {
        asprintf(&str, "%s, %s %d", tmp, inventory_names[i],
        client->elements[i]);
        free(tmp);
        tmp = str;
    }
    asprintf(&str, "%s]\n", tmp);
    free(tmp);
    write_circular_buff(client->write_buff, str == NULL ? "" : str);
    if (str != NULL)
        free(str);
    return 202;
}

int client_inventory(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(0)

    tlist_push(client, in_inventory, 1 / client->g_data->args->freq, NULL);
    return 201;
}
