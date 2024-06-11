/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** circular_buff
*/

#ifndef B_YEP_400_LYN_4_1_ZAPPY_VALENTIN_DURY_CIRCULAR_BUFF_H
    #define B_YEP_400_LYN_4_1_ZAPPY_VALENTIN_DURY_CIRCULAR_BUFF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

typedef struct circular_buff_s
{
    char *buffer;
    char *read_head;
    char *write_head;
} circular_buff_t;

char read_circular_buff(circular_buff_t *buff);
char dec_read_circle_buff(circular_buff_t *buff);

#endif //B_YEP_400_LYN_4_1_ZAPPY_VALENTIN_DURY_CIRCULAR_BUFF_H
