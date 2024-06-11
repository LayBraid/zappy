/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** ServerAddress
*/

#pragma once

#include <arpa/inet.h>
#include <string>
#include "ClientException.hpp"
#include "Socket.hpp"

/**
 * This class encapsulates the server address
 */
class ServerAddress {
    public:
        explicit ServerAddress(std::string machine, int port);
        ~ServerAddress() = default;
        void connect(Socket &socket);

    private:
        struct sockaddr_in _addr;
};
