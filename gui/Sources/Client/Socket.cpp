/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Socket
*/

#include "Client/Socket.hpp"

Socket::Socket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) throw ClientException("Socket creation error");
}
