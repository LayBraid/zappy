/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** objects_management
*/

#include "command.h"

/**
 * @brief [Event] Inform the GUI that a player take an element on his tile
 *
 * @param client
 * @param stone_index
 */
void gui_take_object(client_t *client, int stone_index)
{
    char *response = NULL;

    asprintf(&response, "pgt %d %d", client->id, stone_index);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}

/**
 * @brief [Event] Inform the GUI that a player drop an element on his tile
 *
 * @param client
 * @param stone_index
 */
void gui_drop_object(client_t *client, int stone_index)
{
    char *response = NULL;

    asprintf(&response, "pdr %d %d", client->id, stone_index);
    broadcast(client->g_data->sub_gui, response);
    free(response);
}
