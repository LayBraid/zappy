/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef SOCKET_H_
    #define SOCKET_H_

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>
    #include "inc.h"
    #include "circular_buff.h"

circular_buff_t *new_circular_buff(void);
char *get_next_cmd(circular_buff_t *buff);

#endif //SOCKET_H_
