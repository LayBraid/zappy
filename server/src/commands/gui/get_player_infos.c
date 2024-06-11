/*
** EPITECH PROJECT, 2023
** server
** File description:
** get_player_infos
*/

#include "command.h"

static client_t *get_player_two(team_t *team, int id)
{
    for (int i = 0; team->clients[i] != NULL; i++) {
        if (team->clients[i]->id == id)
            return team->clients[i];
    }
    return NULL;
}

client_t *get_player_by_id(client_t *client, int id)
{
    team_t *team = client->g_data->team_list;

    while (team != NULL) {
        client_t *ret = get_player_two(team, id);
        if (ret != NULL)
            return ret;
        team = team->next;
    }
    return NULL;
}

/**
 * @brief Get the player position and orientation
 *
 * @param client
 * @param args
 * @return int
 */
int gui_get_player_pos(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(1);

    int id = atoi(args[0]);
    char *response = NULL;

    client_t *player = get_player_by_id(client, id);
    if (player == NULL) {
        return 400;
    }

    asprintf(&response, "ppo %d %d %d %d\n", id, player->x, player->y, \
    player->direction);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}

/**
 * @brief Get the player level
 *
 * @param client
 * @param args
 * @return int
 */
int gui_get_player_level(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(1);

    int id = atoi(args[0]);
    char *response = NULL;

    client_t *player = get_player_by_id(client, id);
    if (player == NULL)
        return 400;

    asprintf(&response, "plv %d %d\n", id, player->level);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}

/**
 * @brief Get the player position and inventory
 *
 * @param client
 * @param args
 * @return int
 */
int gui_get_player_inventory(client_t *client, char **args)
{
    REQUIRE_TYPE(GUI);
    REQUIRE_ARGS(1);

    int id = atoi(args[0]);
    char *response = NULL;

    client_t *player = get_player_by_id(client, id);
    if (player == NULL)
        return 400;

    asprintf(&response, "pin %d %d %d %d %d %d %d %d %d %d\n", id, player->x,
    player->y, player->elements[food], player->elements[linemate],
    player->elements[deraumere], player->elements[sibur],
    player->elements[mendiane], player->elements[phiras],
    player->elements[thystame]);
    write_circular_buff(client->write_buff, response);
    free(response);
    return 200;
}
