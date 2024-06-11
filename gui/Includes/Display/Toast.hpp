/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Toast
*/

#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>

#define LIFESPAN 1

#pragma once

class Toast {
public:
    using Clock = std::chrono::steady_clock;

    explicit Toast(std::string message, sf::Font &, sf::Texture &texture, int screenHeight);
    ~Toast() = default;

    std::pair<sf::Text &, sf::Sprite &> getDrawables();
    bool update(int offset);

private:
    sf::Sprite _sprite;
    sf::Text _text;

    float _pos;
    int _screenHeight;

    std::chrono::time_point<Clock> _start;
};
