/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** ServerAddress
*/

#include "Client/ServerAddress.hpp"

ServerAddress::ServerAddress(std::string machine, int port)
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);

    if (inet_pton(AF_INET, machine.c_str(), &_addr.sin_addr) <= 0)
        throw ClientException("Invalid address / Address not supported");
}

void ServerAddress::connect(Socket &socket)
{
    int serv = ::connect(socket.get(), (struct sockaddr *)&_addr, sizeof(_addr));
    if (serv < 0) throw ClientException("Connection failed");
};