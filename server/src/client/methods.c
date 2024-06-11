/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "client.h"

void reply_client(client_t *client, int return_status)
{
    (void)client;

    switch (return_status) {
        case 200:
            SUCCESS_CMD();
            break;
        case 201:
            break;
        case 400:
            INVALID_PARAMS();
            break;
        case 500:
            UNKNOWN_CMD();
            break;
        default: break;
    }
}

int set_fd(client_t *client, fd_set *readfds, int *max_fd)
{
    FD_SET(client->socket.fd, readfds);
    if (client->socket.fd > *max_fd)
        *max_fd = client->socket.fd;
    return 0;
}

int check_read_fd(client_t *client, fd_set *readfds)
{
    if (FD_ISSET(client->socket.fd, readfds)) {
        char wait[1024];
        ssize_t end = read(client->socket.fd, &wait, 1024);
        if (end <= 0) {
            client->status = DISCONNECTED;
            perror("read");
            return 84;
        }
        wait[end] = '\0';

        return handle_req(client, wait);
    }
    return 0;
}

int write_needed(client_t *client)
{
    while (client->write_buff->read_head != client->write_buff->write_head) {
        char c = read_circular_buff(client->write_buff);
        ssize_t check = write(client->socket.fd, &c, 1);
        if (check < 0) {
            dec_read_circle_buff(client->write_buff);
            return 0;
        }
    }

    return 0;
}

int check_disconnect(client_t *client)
{
    if (client->status == DISCONNECTED) {
        if (client->type == CLIENT) {
            write_circular_buff(client->write_buff, "dead\n");
            gui_client_death(client);
            client->g_data->map[client->y][client->x].clients =
            remove_client_from_list(
            client->g_data->map[client->y][client->x].clients, client->id);
            client->team->clients = remove_client_from_list(client->team->clients, client->id);
            remove_client_from_incantation(client->g_data, client->id);
        }
        if (client->type == GUI)
            delete_subscription(client->g_data->sub_gui, client);
        return 1;
    }
    return 0;
}
