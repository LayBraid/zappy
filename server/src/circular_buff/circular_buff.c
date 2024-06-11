/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "circular_buff.h"

circular_buff_t *new_circular_buff(void)
{
    circular_buff_t *buff = malloc(sizeof(circular_buff_t));

    buff->buffer = malloc(sizeof(char) * SIZE);
    memset(buff->buffer, 0, SIZE);
    buff->read_head = buff->buffer;
    buff->write_head = buff->buffer;
    return buff;
}

void free_circular_buff(circular_buff_t *buff)
{
    free(buff->buffer);
    free(buff);
}

char read_circular_buff(circular_buff_t *buff)
{
    char c = *buff->read_head;

    buff->read_head++;
    if (buff->read_head == buff->buffer + SIZE - 1)
        buff->read_head = buff->buffer;
    return c;
}

char dec_read_circle_buff(circular_buff_t *buff)
{
    char c = *buff->read_head;

    buff->read_head--;
    if (buff->read_head == buff->buffer - 1)
        buff->read_head = buff->buffer + SIZE - 1;
    return c;
}

bool write_circular_buff(circular_buff_t *buff, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (buff->write_head == buff->read_head && i != 0)
            return false;
        *buff->write_head = str[i];
        buff->write_head++;
        if (buff->write_head == buff->buffer + SIZE - 1)
            buff->write_head = buff->buffer;
    }
    return true;
}
