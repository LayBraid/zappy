/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** ClientException
*/

#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <utility>

class ClientException : public std::exception {
public:
    explicit ClientException(std::string reason) : _reason(std::move(reason))
    {};

    [[nodiscard]] const char *what() const noexcept override
    {
        return _reason.c_str();
    };


private:
    std::string _reason;
};
