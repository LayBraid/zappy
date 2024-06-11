/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int find_stone(int elements[7], char *stone)
{
    for (int i = 0; i < STONES; i++) {
        if (strcmp(stone, inventory_names[i]) == 0)
            return elements[i] == 0 ? -1 : i;
    }
    return -1;
}

static int take_object_callback(client_t *client, void *args)
{
    int *stone_index = (int *) args;

    gui_take_object(client, *stone_index);
    update_tile(client, client->x, client->y);
    update_player_inventory(client);
    free(args);
    return 200;
}

int client_take_object(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    REQUIRE_ARGS(1)
    int stone_index =
    find_stone(client->g_data->map[client->y][client->x].elements, args[0]);
    int *s_index = NULL;

    if (stone_index == -1) {
        write_circular_buff(client->write_buff, "ko\n");
        return 501;
    }
    client->g_data->map[client->y][client->x].elements[stone_index]--;
    client->elements[stone_index]++;
    s_index = malloc(sizeof(int));
    *s_index = stone_index;
    tlist_push(client, take_object_callback, 7 / client->g_data->args->freq,
    s_index);
    return 250;
}
