/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "criterion/criterion.h"
#include "../include/circular_buff.h"
#include "../include/inc.h"

circular_buff_t *new_circular_buff(void);
void free_circular_buff(circular_buff_t *buff);
char read_circular_buff(circular_buff_t *buff);
char dec_read_circle_buff(circular_buff_t *buff);
int write_circular_buff(circular_buff_t *buff, char *str);
char *get_next_cmd(circular_buff_t *buff);

Test(circular_buff, test1)
{
    circular_buff_t *buff = new_circular_buff();
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 's');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), '\0');
    free_circular_buff(buff);
}

Test(circular_buff, test2)
{
    circular_buff_t *buff = new_circular_buff();
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 's');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 's');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), '\0');
    free_circular_buff(buff);
}

Test(circular_buff, test3)
{
    circular_buff_t *buff = new_circular_buff();
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 's');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 's');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 's');
    cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(read_circular_buff(buff), '\0');
    free_circular_buff(buff);
}

Test(circular_buff, test4)
{
    circular_buff_t *buff = new_circular_buff();
    for (int i = 0; i < 2040; i++)
        cr_assert_eq(write_circular_buff(buff, "t"), true);
    cr_assert_eq(write_circular_buff(buff, "ceci est un test"), false);
}

Test(circular_buff, go_back_to_beginning)
{
    circular_buff_t *buff = new_circular_buff();
    for (int i = 0; i < 1020; i++)
        cr_assert_eq(write_circular_buff(buff, "t"), true);
    for (int i = 0; i < 1020; i++)
        cr_assert_eq(read_circular_buff(buff), 't');
    cr_assert_eq(write_circular_buff(buff, "ceci est un test"), true);
    cr_assert_eq(read_circular_buff(buff), 'c');
    cr_assert_eq(read_circular_buff(buff), 'e');
    cr_assert_eq(read_circular_buff(buff), 'c');
    cr_assert_eq(read_circular_buff(buff), 'i');
}

Test(circular_buff, get_cmd)
{
    circular_buff_t *buff = new_circular_buff();
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "get"), true);
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "\ntest"), true);

    cr_assert_str_eq(get_next_cmd(buff), "testgettest");
}

Test(circular_buff, get_cmd_error)
{
    circular_buff_t *buff = new_circular_buff();
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "get"), true);

    cr_assert_eq(get_next_cmd(buff), NULL);
}

Test(circular_buff, get_cmd_2)
{
    circular_buff_t *buff = new_circular_buff();
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "get"), true);
    cr_assert_eq(write_circular_buff(buff, "test"), true);
    cr_assert_eq(write_circular_buff(buff, "\nniko"), true);

    cr_assert_eq(write_circular_buff(buff, "mouk"), true);
    cr_assert_eq(write_circular_buff(buff, "zebi"), true);
    cr_assert_eq(write_circular_buff(buff, "\ntest"), true);
    cr_assert_str_eq(get_next_cmd(buff), "testgettest");
    cr_assert_str_eq(get_next_cmd(buff), "nikomoukzebi");
}

Test(circular_buff, get_next_cmd_empty)
{
    circular_buff_t *buff = new_circular_buff();

    cr_assert_eq(write_circular_buff(buff, "\n"), true);
    cr_assert_eq(strcmp(get_next_cmd(buff), "500"), 0);
}

Test(circular_buff, get_next_cmd_space)
{
    circular_buff_t *buff = new_circular_buff();

    cr_assert_eq(write_circular_buff(buff, " \n"), true);
    cr_assert_eq(strcmp(get_next_cmd(buff), " "), 0);
}
