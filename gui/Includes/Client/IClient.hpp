/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** IClient
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

class IClient {
public:
    ~IClient() = default;

    /**
     * This method loops until the server is closed.
     * It handles socket selecting and command writing as well as receiving a response from the server !
     */
    virtual void listen() = 0;

    /**
     * This method allows the engine to set the next command
     * @param command: the command to send to the server
     */
    virtual void setCommand(std::string command) = 0;

    virtual CircularBuffer &getBuffer() = 0;
};