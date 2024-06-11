/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "main.h"

int main(int ac, char **av)
{
    signal(SIGINT, (__sighandler_t)sigint_handler);
    args_t *args = parse_args(ac, av);
    if (args == NULL) {
        printf(USAGE);
        return 84;
    }
    server_t *serv = new_server(args);
    int ret = run_serv(serv);
    close_game(serv);
    delete_server(serv);
    return ret;
}
