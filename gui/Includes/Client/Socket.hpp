/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Socket
*/

#pragma once

#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "ClientException.hpp"

/**
 * This class encapsulates the socket
 */
class Socket {
public:
    Socket();
    ~Socket() = default;
    int get() { return _socket; };

private:
    int _socket;
};