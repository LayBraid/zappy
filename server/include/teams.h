/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef TEAMS_H_
    #define TEAMS_H_

    #include "client.h"

team_t *create_teams(args_t *args);
team_t *find_team(team_t *team, char *name);
char *has_winner_team(team_t *teams);
egg_t *create_eggs(args_t *args);
egg_t *add_egg(team_t *team, args_t *args);
extern void moov_player(client_t *client, int x, int y);
extern client_t **add_client_to_list(client_t **clients, client_t *client);
extern client_t **remove_client_from_list(client_t **clients, int id);
extern int clients_len(client_t **clients);
egg_t *fork_egg(team_t *team, client_t *client);


#endif //TEAMS_H_
