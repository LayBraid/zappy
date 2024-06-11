/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static void add_client_to_team(team_t *team, client_t *client)
{
    int i = 0;

    while (team->clients[i] != NULL)
        i++;
    team->clients[i] = client;
    team->clients[i + 1] = NULL;
    team->places--;
    client->team = team;
}

static int spawn_in_egg(team_t *team, client_t *client)
{
    egg_t *egg = team->egg_list;
    int id = egg->id;

    client->x = egg->x;
    client->y = egg->y;
    client->direction = egg->direction;
    team->egg_list = team->egg_list->next;
    client->elements[0] = 10;
    for (int i = 1; i < STONES; i++)
        client->elements[i] = 0;
    client->g_data->map[egg->y][egg->x].clients =
    add_client_to_list(client->g_data->map[egg->y][egg->x].clients, client);
    free(egg);
    return id;
}

int client_connect(client_t *client, char **args)
{
    REQUIRE_TYPE(UNKNOWN);
    REQUIRE_ARGS(1)
    char *response = NULL;
    team_t *team = find_team(client->g_data->team_list, args[0]);

    if (team == NULL || team->places == 0) {
        write_circular_buff(client->write_buff, "ko\n");
        return 400;
    }
    add_client_to_team(team, client);
    asprintf(&response, "%d\n%d %d\n", team->places,
    client->g_data->args->width, client->g_data->args->height);
    int egg_id = spawn_in_egg(team, client);
    write_circular_buff(client->write_buff, response);
    free(response);
    client->type = CLIENT;
    client->time_spawn = time(NULL);
    gui_new_connection(client);
    gui_client_connection_for_an_egg(client, egg_id);
    return 200;
}
