/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "server.h"
#include "client.h"

void push(client_t **list, client_t *new_sock)
{
    if (list == NULL)
        return;
    if (*list == NULL) {
        *list = new_sock;
        return;
    }
    client_t *tmp = *list;
    while (tmp->next) {
        tmp = tmp->next;
    }

    tmp->next = new_sock;
    true;
}

void delete(client_t *to_delete, client_t **list)
{
    if (*list == NULL)
        return;
    client_t *tmp = *list;
    if (tmp == to_delete) {
        *list = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next) {
        if (tmp->next == to_delete) {
            tmp->next = tmp->next->next;
            free(to_delete);
            return;
        }
        tmp = tmp->next;
    }
}

client_t *get_client(client_t **list, int fd)
{
    client_t *tmp = *list;
    while (tmp) {
        if (tmp->socket.fd == fd) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

int delete_client(client_t *to_delete, client_t **list)
{
    if (to_delete->data_socket) {
        delete_data_socket(to_delete->data_socket);
    }
    close(to_delete->socket.fd);
    if (to_delete->username)
        free(to_delete->username);
    free_circular_buff(to_delete->read_buff);
    free_circular_buff(to_delete->write_buff);
    delete(to_delete, list);
    return 0;
}
