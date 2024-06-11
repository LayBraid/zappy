/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** FileDescriptors
*/

#pragma once

#include "Socket.hpp"

/**
 * This class encapsulates file descriptors and their usage within the project's context
 */
class FileDescriptors {

public:
    explicit FileDescriptors(int);
    ~FileDescriptors() = default;

    void select(int socket);
    fd_set &get() { return _fileDescriptors; };

private:
    fd_set _fileDescriptors = (fd_set) {0};
    int _maxFileDescriptors;
    struct timeval _timeout{0, 100};

};
