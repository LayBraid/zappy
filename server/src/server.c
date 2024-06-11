/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "server.h"

server_t *new_server(args_t *args)
{
    server_t *server = malloc(sizeof(server_t));
    if (server == NULL)
        return (NULL);

    server->control_socket = new_control_socket(args->port);
    server->client_list = NULL;
    server->g_data = new_data(args);
    server->g_data->client_list = NULL;
    server->sub_players = new_subscription("players");
    srand(time(NULL));
    return server;
}

void *delete_server(server_t *server)
{
    if (server == NULL)
        return NULL;
    close(server->control_socket->fd);
    free(server->control_socket);
    while (server->client_list) {
        delete_client(server->client_list, &server->client_list);
    }
    free(server);
    return NULL;
}

static void hand_con(server_t *serv)
{
    client_t *client = get_client(&serv->client_list, \
    serv->control_socket->fd);
    if (client) {
        return;
    }
    client = new_client(serv->control_socket->fd, serv->g_data, \
    serv->sub_players);
    push(&serv->client_list, client);
    serv->g_data->client_list = serv->client_list;
    write_circular_buff(client->write_buff, "WELCOME\n");
}

static void for_eachs(server_t *serv)
{
    FOR_EACH(&serv->client_list, tlist_consume, time(NULL));
    FOR_EACH(&serv->client_list, check_read_fd, &serv->readfds);
    FOR_EACH(&serv->client_list, handle_commands);
    FOR_EACH(&serv->client_list, write_needed);
    FOR_EACH(&serv->client_list, check_disconnect);
    FOR_EACH(&serv->client_list, eat_timer);
    FOR_EACH(&serv->client_list, death_timer);
}

int run_serv(server_t *serv)
{
    serv->readfds = (fd_set){0};
    int max_fd = serv->control_socket->fd;
    while (!sigint(false) && serv->g_data->winners == NULL) {
        FD_ZERO(&serv->readfds);
        FD_SET(serv->control_socket->fd, &serv->readfds);
        FOR_EACH(&serv->client_list, set_fd, &serv->readfds, &max_fd);
        struct timeval timeout = {0, 1000};
        int ac = select(max_fd + 1, &serv->readfds, NULL, NULL, &timeout);
        if (ac == -1) return 84;
        if (FD_ISSET(serv->control_socket->fd, &serv->readfds)) hand_con(serv);
        for_eachs(serv);
        refill(serv->g_data);
    }
    return 0;
}
