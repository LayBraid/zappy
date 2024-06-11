/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** ResourceDrawer
*/

#include "Tile.hpp"
#include <memory>
#include <random>

#pragma once

class ResourceDrawer {
public:
    ResourceDrawer();
    ~ResourceDrawer() = default;

    sf::Sprite &getItemSprite(Resource resource);

    void drawFood(sf::RenderWindow &window, int amount, float x, float y);
    void drawResource(sf::RenderWindow &window, int amount, float x, float y, int i);
    void drawResources(sf::RenderWindow &window, const std::shared_ptr<Tile> &tile);

private:
    sf::Texture _resourceTexture;
    sf::Texture _foodTexture;

    sf::Sprite _resourceSprite;
    sf::Sprite _foodSprite;
};