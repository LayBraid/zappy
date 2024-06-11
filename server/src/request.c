/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "request.h"

int handle_req(client_t *client, char *rec)
{
    bool success = write_circular_buff(client->read_buff, rec);
    if (!success) {
        return 1;
    }
    return 0;
}

static char **unmarshall(char *rec)
{
    char **args = malloc(sizeof(char *) * (occurence(rec, ' ') + 2));
    char *token = strtok(rec, " ");
    int i = 0;
    while (token) {
        args[i] = strdup(token);
        args[i][strlen(args[i])] = '\0';
        remove_trailing(args[i]);
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    return args;
}

static bool invalid(char *cmd)
{
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] != ' ')
            return false;
    }
    free(cmd);
    return true;
}

static bool search_cmd(client_t *client, char **args)
{
    for (int i = 0; i < NB_CMD; i++) {
        if (strcmp(args[0], commands[i].cmd) == 0) {
            int return_status = commands[i].func(client, args + 1);
            reply_client(client, return_status);
            free_tab(args);
            return true;
        }
    }
    if (client->type == UNKNOWN) {
        if (client_connect(client, args) == 501)
            return false;
        free_tab(args);
        return true;
    }
    return false;
}

int handle_commands(client_t *client)
{
    if (client->incantation)
        return 0;
    char *cmd = get_next_cmd(client->read_buff);
    if (!cmd) return 0;
    if (invalid(cmd)) {
        UNKNOWN_CMD();
        return 0;
    }
    char **args = unmarshall(cmd);
    free(cmd);
    if (!args[0]) {
        UNKNOWN_CMD();
        return 0;
    }
    if (search_cmd(client, args)) {
        return 0;
    }
    UNKNOWN_CMD();
    free_tab(args);
    return 0;
}
