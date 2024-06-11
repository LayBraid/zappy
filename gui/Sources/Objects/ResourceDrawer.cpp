/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** ResourceDrawer
*/

#include "Objects/ResourceDrawer.hpp"

ResourceDrawer::ResourceDrawer()
{
    _foodTexture.loadFromFile("gui/asset/food.png");
    _resourceTexture.loadFromFile("gui/asset/resources.png");

    _foodSprite.setTexture(_foodTexture);
    _resourceSprite.setTexture(_resourceTexture);

    _resourceSprite.setScale(1.5, 1.5);
    _foodSprite.setScale(0.3, 0.3);
};

sf::Sprite &ResourceDrawer::getItemSprite(Resource resource)
{
    if (resource == FOOD) return _foodSprite;

    sf::IntRect resourceRect = {0,resource * 24,24,24};
    _resourceSprite.setTextureRect(resourceRect);
    return _resourceSprite;
}

void ResourceDrawer::drawResource(sf::RenderWindow &window, int amount, float x, float y, int i)
{
    for (int count = 0; count < amount; count++) {
        _resourceSprite.setPosition(x + count * 10,
                                    y + i * 10);
        window.draw(_resourceSprite);
    }
}

void ResourceDrawer::drawFood(sf::RenderWindow &window, int amount, float x, float y)
{
    if (amount == 0) return;

    _foodSprite.setTextureRect({ amount % 14 * 126, amount % 2 * 126, 126, 126 });
    _foodSprite.setPosition(x, y);
    window.draw(_foodSprite);
}

void ResourceDrawer::drawResources(sf::RenderWindow &window, const std::shared_ptr<Tile> &tile)
{
    auto resources = tile->getResources();
    auto x = (tile->getPosX() - tile->getPosY()) * tile->getSize().first;
    auto y = (tile->getPosX() + tile->getPosY()) * tile->getSize().second + tile->getSize().second;

    sf::IntRect resourceRect = {0,0,24,24};
    for (size_t i = 0; i < FOOD; i++) {
        resourceRect.top = 24 * i;
        _resourceSprite.setTextureRect(resourceRect);
        drawResource(window, resources.at(i), x, y, i);
    }

    drawFood(window, resources.at(FOOD), x, y);
}