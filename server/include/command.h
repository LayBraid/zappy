/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define _GNU_SOURCE

    #include <fcntl.h>
    #include <sys/wait.h>
    #include <time.h>
    #include "request.h"
    #include "subscription.h"
    #include "incantation.h"

    #define NB_CMD 22

    #define PLAYER_INFOS  "pnw %d %d %d %d %d %s\npin %d %d %d " \
"%d %d %d %d %d %d %d\n"

// Gui
extern int gui_connect(client_t *client, char **args);
extern int gui_get_tile(client_t *client, char **args);
extern int gui_get_all_tiles(client_t *client, char **args);
extern int gui_map_size(client_t *client, char **args);
extern int gui_get_teams(client_t *client, char **args);
extern int gui_get_player_pos(client_t *client, char **args);
extern int gui_get_player_level(client_t *client, char **args);
extern int gui_get_player_inventory(client_t *client, char **args);
extern int gui_get_time_unit(client_t *client, char **args);
extern int gui_set_time_unit(client_t *client, char **args);
extern void gui_new_connection(client_t *client); // Event
extern void gui_expulsion(client_t *client); // Event
extern void gui_broadcast(client_t *client, char *msg); // Event
extern void gui_start_incantation(client_t *client, client_t **clients);
extern void gui_end_incantation(client_t *client, int x, int y, bool result);
extern void gui_egg_laying_by_client(client_t *client); // Event
extern void gui_take_object(client_t *client, int stone_index); // Event
extern void gui_drop_object(client_t *client, int stone_index); // Event
extern void gui_client_death(client_t *client); // Event
extern void gui_egg_was_laid_by_client(client_t *client, egg_t *egg); // Event
extern void gui_client_connection_for_an_egg(client_t *client, int egg_id);
extern void gui_egg_death(client_t *client, egg_t *egg); // Event
extern void gui_end_game(global_data_t *g_data, char *winner_name); // Event
extern void gui_message_from_server(client_t *client); // Event

extern void update_player_level(client_t *client);
extern void update_player_inventory(client_t *client);
extern void update_player_position(client_t *client);
extern void update_tile(client_t *client, int x, int y);
extern void update_tile_gdata(global_data_t *gdata, int x, int y);

// Client
extern int client_connect(client_t *client, char **args);
extern int client_left(client_t *client, char **args);
extern int client_right(client_t *client, char **args);
extern int client_forward(client_t *client, char **args);
extern int client_look(client_t *client, char **args);
extern int client_connect_nbr(client_t *client, char **args);
extern int client_inventory(client_t *client, char **args);
extern int client_drop_object(client_t *client, char **args);
extern int client_take_object(client_t *client, char **args);
extern int client_broadcast(client_t *client, char **args);
extern int client_fork(client_t *client, char **args);
extern int client_incantation(client_t *client, char **args);
extern int client_eject(client_t *client, char **args);

void close_game(server_t *serv);

int handle_res(client_t *client, int status);

int tab_len(char **tab);
int incantation_response(client_t *client, void *args);
int find_stone(int elements[7], char *stone);

extern const commands_t commands[NB_CMD];
extern const char inventory_names[7][10];
extern const int prerequisite[7][STONES];

    #define REQUIRE_ARGS(n) \
    if (tab_len(args) < n) { \
    write_circular_buff(client->write_buff, \
    client->type == GUI ? "sbp\n" : "ko\n"); \
        return 501; \
    }

    #define REQUIRE_TYPE(x) \
    if (client->type != x) { \
        write_circular_buff(client->write_buff, \
        client->type == GUI ? "suc\n" : "ko\n"); \
        return 501; \
    }

int write_needed(client_t *client);
data_socket_t *new_data_socket(int parent_socket);
data_socket_t *connect_data_socket(data_socket_t *data_sock, int port, \
char *ip);

// time cmds
void tlist_push(client_t *client, time_func func, short int end, void *args);

char **str_split(char *str, char c);

int sanmove_x(int x, int width, int direction);
int sanmove_y(int y, int width, int direction);
int look_x(client_t *client, int i, int j);
int look_y(client_t *client, int i, int j);
int sound_tile_calc(int a, bool left);
int vector_calc(int a, int b, int max);

#endif //COMMAND_H_
