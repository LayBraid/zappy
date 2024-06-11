#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <array>
#include <iostream>

#pragma once

class Launcher
{
private:
    sf::RenderWindow _window;
    sf::Event _event;
    sf::Font _font;
    sf::Text _content;
    sf::Clock _clock;

    sf::Text _address;
    sf::Text _port;

    std::array<sf::Color, 2> _colors;
    unsigned int _colorIndex = 0;

    unsigned int _currentParam = 0;

    std::string defaultAddress;
    std::string defaultPort;

    bool _validArgs = true;

    sf::Texture _texture;
    sf::Sprite _background;

public:
    Launcher(int ac, char *av[]);
    ~Launcher();

    bool display(
    std::shared_ptr<std::string> &address, std::shared_ptr<std::string> &port);

    void printHelpMessage();
};