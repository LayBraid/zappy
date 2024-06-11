/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Client
*/

#include "Client/Client.hpp"

#define SET_ARG(variable, value)    {                                  \
                                    i++;                               \
                                    if (i >= ac)                       \
                                    printHelpMessage();                \
                                    variable = value;                  \
                                    }

Client::Client(int ac, char **av)
{
    if (ac <= 1) printHelpMessage();
    for (int i = 1; i < ac; i++) {
        auto arg = std::string(av[i]);
        if (arg == "-p") SET_ARG(_port, std::atoi(av[i]));
        if (arg == "-h") SET_ARG(_machine, std::string(av[i]));
        if (arg == "-help") printHelpMessage();
    }
    if (_port == 0) printHelpMessage();
    try {
        _addr = std::make_shared<ServerAddress>(_machine, _port);
        _addr->connect(_socket);
        _fds = std::make_shared<FileDescriptors>(_socket.get());
    }
    catch (ClientException &error) {
        std::cerr << error.what() << std::endl;
        _connected = false;
    }
}

Client::Client(const std::string &address, unsigned short port) {
    _machine = address;
    _port = port;
    try {
        _addr = std::make_shared<ServerAddress>(_machine, _port);
        _addr->connect(_socket);
        _fds = std::make_shared<FileDescriptors>(_socket.get());
    }
    catch (ClientException &error) {
        std::cerr << error.what() << std::endl;
        _connected = false;
    }
}

void Client::printHelpMessage()
{
    std::cout << "./zappy_gui -help" << std::endl;
    std::cout << "\tUSAGE: ./zappy_ai -p port -h machine" << std::endl;
    std::cout << "\tport is the port number" << std::endl;
    std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
    _connected = false;
}

int Client::receive()
{
    char wait[SIZE];
    ssize_t end = read(_socket.get(), &wait, SIZE);
    if (end == -1) throw ClientException("Read failed");
    wait[end] = '\0';
    return _buff.write(wait);
}

void Client::setCommand(std::string command)
{
    if (_command.empty()) {
        _command = std::move(command);
        return;
    }
    _command += std::move(command);
}

void Client::listen()
{
    _fds->select(_socket.get());
    if (!_command.empty()) {
        std::cout << _command << std::endl;
        write(_socket.get(), _command.c_str(), _command.length());
        _command.clear();
    }
    if (FD_ISSET(_socket.get(), &_fds->get()))
        receive();
}
