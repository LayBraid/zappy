/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** FileDescriptors
*/

#include "Client/FileDescriptors.hpp"

FileDescriptors::FileDescriptors(int socket): _maxFileDescriptors(socket)
{
}

void FileDescriptors::select(int socket)
{
    FD_ZERO(&_fileDescriptors);
    FD_SET(0, &_fileDescriptors);
    FD_SET(socket, &_fileDescriptors);
    if (socket > _maxFileDescriptors) _maxFileDescriptors = socket;

    ::select(_maxFileDescriptors + 1, &_fileDescriptors, nullptr, nullptr, &_timeout);
}
