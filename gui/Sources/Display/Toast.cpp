/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Toast
*/

#include <iostream>
#include "Display/Toast.hpp"

Toast::Toast(std::string message, sf::Font &font, sf::Texture &texture, int screenHeight) : _pos(screenHeight), _screenHeight(screenHeight)
{
    _start = Clock::now();

    _sprite.setTexture(texture);
    _sprite.setScale(3, 3);

    _text.setFont(font);
    _text.setOutlineColor(sf::Color::White);
    _text.setOutlineThickness(1);
    _text.setCharacterSize(20);
    _text.setString(message);
}

std::pair<sf::Text &, sf::Sprite &> Toast::getDrawables()
{
    return { _text, _sprite };
}

bool Toast::update(int offset)
{
    auto pos = _pos - offset * 100;

    _sprite.setPosition(0, pos);
    _text.setPosition(20, pos + 30);
    if (pos > _screenHeight - offset * 100 - 100) {
        _pos -= 0.3;
        return false;
    }

    auto t1 = Clock::now();
    std::chrono::duration<double> time_span = duration_cast<std::chrono::duration<double>>(t1 - _start);
    auto opacity = std::max((int)(255 - time_span.count() / LIFESPAN * 255), 0);

    _sprite.setColor(sf::Color(255, 255, 255, opacity));
    _text.setOutlineColor(sf::Color(255, 255, 255, opacity));
    _text.setFillColor(sf::Color(0, 0, 0, opacity));

    if (time_span.count() > 5)
        return true;
    return false;
}