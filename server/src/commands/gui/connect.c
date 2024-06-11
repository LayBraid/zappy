/*
** EPITECH PROJECT, 2023
** server
** File description:
** connect
*/

#include "command.h"

static void send_all_players_informations(client_t *client)
{
    for (client_t *tmp = client->g_data->client_list; tmp; tmp = tmp->next) {
        if (tmp->type == CLIENT) {
            dprintf(client->socket.fd, PLAYER_INFOS, tmp->id, tmp->x, tmp->y,
            tmp->direction, tmp->level, tmp->team->name, tmp->id, tmp->x,
            tmp->y, tmp->elements[food], tmp->elements[linemate],
            tmp->elements[deraumere], tmp->elements[sibur],
            tmp->elements[mendiane], tmp->elements[phiras],
            tmp->elements[thystame]);
        }
    }
}

/**
 * @brief Connect a GUI to the server and execute some initial commands
 *
 * @param client
 * @param args
 * @return int
 */
int gui_connect(client_t *client, char **args)
{
    REQUIRE_TYPE(UNKNOWN);
    REQUIRE_ARGS(0);

    client->type = GUI;
    gui_map_size(client, args);
    gui_get_time_unit(client, args);
    write_needed(client);
    gui_get_all_tiles(client, args);
    gui_get_teams(client, args);
    write_needed(client);
    subscribe(client->g_data->sub_gui, &client);
    send_all_players_informations(client);
    return 200;
}
