/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "socket.h"

socket_t *new_control_socket(int connection_port)
{
    socket_t *control_sock = malloc(sizeof(socket_t));
    if (control_sock == NULL)
        return (NULL);
    control_sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (control_sock->fd == -1)
        perror("creating socket");
    control_sock->saddr.sin_family = AF_INET;
    control_sock->saddr.sin_port = htons(connection_port);
    control_sock->saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(control_sock->fd, (const struct sockaddr *)&control_sock->saddr,
            sizeof(struct sockaddr_in)) == -1) {
        perror("binding socket");
        return NULL;
    }
    if (listen(control_sock->fd, 20) == -1) {
        perror("listen socket");
        return NULL;
    }
    return control_sock;
}

static void init_data_socket(data_socket_t *data_sock, int parent_fd)
{
    data_sock->read_buff = new_circular_buff();
    data_sock->parent_fd = parent_fd;
    data_sock->sock.fd = socket(PF_INET, SOCK_STREAM, 0);
    data_sock->sock.saddr.sin_family = PF_INET;
    data_sock->sock.saddr.sin_port = htons(0);
    data_sock->sock.saddr.sin_addr.s_addr = INADDR_ANY;
}

data_socket_t *new_data_socket(int parent_fd)
{
    data_socket_t *data_sock = malloc(sizeof(data_socket_t));
    if (data_sock == NULL) return (NULL);
    init_data_socket(data_sock, parent_fd);
    if (bind(data_sock->sock.fd,
    (const struct sockaddr *)&(data_sock->sock.saddr),
    sizeof(struct sockaddr_in)) == -1) {
        perror("binding socket");
        return NULL;
    }
    if (listen(data_sock->sock.fd, 2) == -1) {
        perror("listen socket");
        return NULL;
    }
    size_t len = sizeof(data_sock->sock.saddr);
    getsockname(data_sock->sock.fd,
    (struct sockaddr *)&(data_sock->sock.saddr), (socklen_t *)&len);
    return data_sock;
}

data_socket_t *connect_data_socket(data_socket_t *data_sock, int port, char *ip)
{
    data_sock->sock.saddr.sin_port = htons(port);
    data_sock->sock.saddr.sin_addr.s_addr = inet_addr(ip);
    if (connect(data_sock->sock.fd,
    (const struct sockaddr *)&(data_sock->sock.saddr),
    sizeof(struct sockaddr_in)) == -1) {
        perror("connecting socket");
        return NULL;
    }
    return data_sock;
}

void delete_data_socket(data_socket_t *data_sock)
{
    close(data_sock->sock.fd);
    free(data_sock);
}
