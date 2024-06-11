/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

const commands_t commands[NB_CMD] = {
        {"GRAPHIC", gui_connect},
        {"bct", gui_get_tile},
        {"mct", gui_get_all_tiles},
        {"msz", gui_map_size},
        {"tna", gui_get_teams},
        {"sgt", gui_get_time_unit},
        {"sst", gui_set_time_unit},
        {"ppo", gui_get_player_pos},
        {"plv", gui_get_player_level},
        {"pin", gui_get_player_inventory},
        {"Forward", client_forward},
        {"Right", client_right},
        {"Left", client_left},
        {"Look", client_look},
        {"Connect_nbr", client_connect_nbr},
        {"Inventory", client_inventory},
        {"Take", client_take_object},
        {"Set", client_drop_object},
        {"Broadcast", client_broadcast},
        {"Fork", client_fork},
        {"Incantation", client_incantation},
        {"Eject", client_eject},
};
