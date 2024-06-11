/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef MAIN_H_
    #define MAIN_H_

    #include <stdlib.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <signal.h>
    #include "server.h"
    #include "inc.h"

typedef void (*__sighandler_t)(int); // MacOSl

server_t *new_server(args_t *args);
void *delete_server(server_t *server);
int run_serv(server_t *serv);

void sigint_handler(void);

    #define USAGE "USAGE: ./zappy_server -p port -x width -y height -n name1 \
name2 ... -c clients_nb " \
"-f freq\n" \
"\tport is the port number\n" \
"\twidth is the width of the world\n" \
"\theight is the height of the world\n" \
"\tnameX is the name of the team X\n" \
"\tclients_nb is the number of authorized clients per team\n" \
"\tfreq is the reciprocal of time unit for execution of actions\n"

#endif //MAIN_H_
