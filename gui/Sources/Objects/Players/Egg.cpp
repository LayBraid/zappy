/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Egg
*/

#include "Objects/Players/Egg.hpp"

Egg::Egg(unsigned int id, unsigned int x, unsigned int y, std::string teamName)
        : APlayer(id, x, y, teamName),
         _displayPosX(x), _displayPosY(y)
{
    _eggTexture.loadFromFile("gui/asset/Egg/Egg.png");
    setSprite({genSprite(_eggTexture), genSprite(_eggTexture)});
    setSpriteGrid({4,2});
    getSprite().first->setScale(0.5, 0.5);
    getSprite().second->setScale(0.5, 0.5);
};

void Egg::update(int tileWidth, int tileHeight)
{
    auto [x, y] = getRelativePos(tileWidth, tileHeight);
    
    const auto [sizeX, sizeY] = getSpriteSize();
    sf::IntRect rect(sizeX * EGG_SIZE, sizeY * EGG_SIZE, EGG_SIZE, EGG_SIZE);

    auto [body, shadow] = getSprite();
    body->setPosition(x, y);
    body->setTexture(_eggTexture);
    body->setTextureRect(rect);

    shadow->setPosition(x, y);
    shadow->setTexture(_eggTexture);
    shadow->setTextureRect(rect);

    updateFrame();
}
