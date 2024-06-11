/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static char *get_message(char **args)
{
    int len = tab_len(args) + 1;
    char *message = NULL;

    if (args == NULL)
        return NULL;
    for (int i = 0; args[i]; i++)
        len += strlen(args[i]);
    message = malloc(sizeof(char) * len);
    message[0] = '\0';
    for (int i = 0; args[i]; i++) {
        strcat(message, args[i]);
        strcat(message, " ");
    }
    return message;
}

static int come_from_left(int x, int y, int dir)
{
    if ((dir == N && x > 0) || (dir == S && x < 0))
        return true;
    return ((dir == E && y > 0) || (dir == W && y < 0));
}

static void send_to_client(client_t *client, int x, int y, char *message)
{
    char *response = NULL;
    int vector[2] = {vector_calc(client->x, x, client->g_data->args->width),
    vector_calc(client->y, y, client->g_data->args->height)};
    int ac[2] = {client->direction == E ? 1 : client->direction == W ? -1 : 0,
    client->direction == S ? 1 : client->direction == N ? -1 : 0};
    int scalair = vector[0] * ac[0] + vector[1] * ac[1];
    double lengths = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
    double angle = lengths == 0 ? 0 : acos(scalair / lengths);
    double degree_angle = angle * (180.0 / M_PI);
    bool left = come_from_left(vector[0], vector[1], client->direction);
    int sound_tile = sound_tile_calc((int)degree_angle, left);

    if (vector[0] == 0 && vector[1] == 0)
        sound_tile = 0;
    asprintf(&response, "message %d, %s\n", sound_tile, message);
    write_circular_buff(client->write_buff, response);
    free(response);
}

static int broadcast_response(client_t *client, void *args)
{
    char *message = (char *)args;

    for (client_t *tmp = client->g_data->client_list; tmp != NULL; \
    tmp = tmp->next) {
        if (tmp->type == CLIENT && tmp->id != client->id)
            send_to_client(tmp, client->x, client->y, message);
    }
    gui_broadcast(client, message);
    free(message);
    return 200;
}

int client_broadcast(client_t *client, char **args)
{
    REQUIRE_TYPE(CLIENT);
    char *message = get_message(args);

    if (message == NULL)
        return 400;
    tlist_push(client, broadcast_response, 7 / client->g_data->args->freq,
    message);
    return 201;
}
