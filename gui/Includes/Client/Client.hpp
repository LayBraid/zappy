/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Client
*/

#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <cstring>
#include <map>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "Socket.hpp"
#include "ServerAddress.hpp"
#include "ClientException.hpp"
#include "CircularBuffer.hpp"
#include "Constants.hpp"
#include "Response.hpp"
#include "FileDescriptors.hpp"
#include "IClient.hpp"

class Client : public IClient {
public:
    explicit Client(int ac, char **av);
    Client(const std::string &address, unsigned short port);
    
    ~Client() = default;

    /**
     * This method loops until the server is closed.
     * It handles socket selecting and command writing as well as receiving a response from the server !
     */
    void listen();

    /**
     * This is a simple method which prints the help message and closes the server with the `_connected = false` statement
     */
    void printHelpMessage();

    /**
     * Simple method to access the _connected field from outside the class.
     * @return the _connected bool
     */
    bool isConnected() const { return _connected; };

    /**
     * This method reads from the socket and writes the data into the circular buffer.
     * @return the value of _buff.write()
     */
    int receive();

    /**
     * This method allows the engine to set the next command
     * @param command: the command to send to the server
     */
    void setCommand(std::string command);

    CircularBuffer &getBuffer() { return _buff; };

private:
    unsigned short _port = 0;
    std::string _machine = "127.0.0.1";
    std::shared_ptr<ServerAddress> _addr;
    Socket _socket;
    CircularBuffer _buff;
    std::shared_ptr<FileDescriptors> _fds;
    std::condition_variable _dataReady;
    std::string _command = "GRAPHIC\n";
    bool _connected = true;
};