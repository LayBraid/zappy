/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** HUD
*/

#include <memory>
#include <SFML/Graphics.hpp>
#include "Objects/IObject.hpp"
#include "Objects/Players/Player.hpp"
#include "Objects/ResourceDrawer.hpp"
#include "Toast.hpp"

#pragma once

const static std::array<std::string, 5> directions = {
        "Unknown", "North", "East", "South", "West"
};
const static std::array<std::string, 3> playerLabels = {
        "Position", "Orientation", "Level"
};

const static std::array<std::string, 7> labels = {
        "Food", "Linemate", "Deraumere", "Sibur",
        "Mendiane", "Phiras", "Thystame"
};

class HUD {

public:
    HUD(std::shared_ptr<sf::RenderWindow>, std::shared_ptr<ResourceDrawer>, int screenWidth, int screenHeight);
    ~HUD() = default;

    /**
     * Display additional information for a player
     */
    void displayPlayerInfo(std::shared_ptr<Player> &player);

    void displayResourceInfo(std::array<int, 7> quantity);

    void displayInformationMenu(std::shared_ptr<IObject> &object);

    void addToast(std::string message);

    void displayToasts();

private:
    std::vector<std::shared_ptr<Toast>> _toasts;
    std::shared_ptr<ResourceDrawer> _resourceDrawer;

    sf::View _view;
    sf::Font _font;
    sf::Text _text;
    sf::Texture _texture;
    sf::Sprite _infoMenu;
    std::shared_ptr<sf::RenderWindow> _window;
    int _screenHeight;
    int _screenWidth;

    int _offsetX;
    float _offsetY;
};
