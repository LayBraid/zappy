/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** CircularBuffer
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "circular_buff.h"

extern "C" {
    bool write_circular_buff(circular_buff_t *buff, char *str);
    circular_buff_t *new_circular_buff(void);
    void free_circular_buff(circular_buff_t *buff);
    char *get_next_cmd(circular_buff_t *buff);
}

/**
 * This class encapsulates the circular buffer implementation in C
 */
class CircularBuffer {
    public:
        CircularBuffer()
        {
            _buff = new_circular_buff();
        };
        ~CircularBuffer()
        {
            free_circular_buff(_buff);
        };

        char read() { return read_circular_buff(_buff); }
        char decRead() { return dec_read_circle_buff(_buff); };
        bool write(char *str) { return write_circular_buff(_buff, str); };

        std::string getNextCommand()
        {
            char const *cmd = get_next_cmd(_buff);
            if (!cmd) return "";
            return cmd;
        };

    private:
        circular_buff_t *_buff;
};
