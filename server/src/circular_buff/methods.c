/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "circular_buff.h"

static bool is_empty(circular_buff_t *buff)
{
    if (*buff->read_head && buff->read_head[0] == '\n') {
        read_circular_buff(buff);
        return true;
    }
    return false;
}

static bool is_a_cmd(circular_buff_t *buff)
{
    bool is_a_cmd = false;
    for (int j = 0; &buff->read_head[j] != buff->write_head; j++)
        if (buff->read_head[j] == '\n') {
            return true;
        }
    return is_a_cmd;
}

char *get_next_cmd(circular_buff_t *buff)
{
    if (buff->read_head == buff->write_head) return NULL;
    char line[1024];
    int i = 0;
    if (is_empty(buff)) return strdup("500");
    if (!is_a_cmd(buff)) return NULL;
    for (; *buff->read_head && *buff->read_head != '\n'; i++)
        line[i] = read_circular_buff(buff);
    line[i] = '\0';
    read_circular_buff(buff);
    char *to_return = malloc(sizeof(char) * (strlen(line) + 1));
    strcpy(to_return, line);
    to_return[strlen(line)] = '\0';
    return to_return;
}
