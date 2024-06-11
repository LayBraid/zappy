/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Egg
*/

#include "APlayer.hpp"

#define EGG_SIZE 260

#pragma once

class Egg : public APlayer
{

public:
    Egg(unsigned int id, unsigned int x, unsigned int y, std::string teamName);

    void update(int tileWidth, int tileHeight) override;
    std::pair<float, float> getDisplayPos() override { return { _displayPosX, _displayPosY }; };
    void resetDisplayPos() override { _displayPosX = _posX; _displayPosY = _posY; };

private:
    sf::Texture _eggTexture;

    float _displayPosX;
    float _displayPosY;
};