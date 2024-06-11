/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Player
*/

#pragma once

#include "APlayer.hpp"
#define PLAYER_SIZE 256

class Player : public APlayer
{

public:
    Player(unsigned int id, unsigned int x, unsigned int y,
            Orientation orientation, unsigned int level,
            std::string teamName, PlayerTexture &textures, sf::Color color);

    bool movement();
    void updateSprite(float x, float y, sf::IntRect rect, PlayerTexture::TextureVector &vector, sf::Sprite &sprite);
    void setLevel(unsigned int);
    unsigned int getLevel() const;
    Orientation getOrientation() const;
    bool isInitialised() const;
    void setOrientation(Orientation orientation);

    void update(int tileWidth, int tileHeight) override;
    std::pair<float, float> getDisplayPos() override { return { _displayPosX, _displayPosY }; };
    void resetDisplayPos() override { _displayPosX = _posX; _displayPosY = _posY; };

private:
    PlayerTexture &_playerTexture;
    unsigned int _level;
    Orientation _orientation = NORTH;
    int _angle = 0;
    bool _initialised = false;

    float _displayPosX;
    float _displayPosY;

    sf::Color _color;
};
