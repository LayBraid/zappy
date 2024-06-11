/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Player
*/

#include "Objects/Players/Player.hpp"

Player::Player(unsigned int id, unsigned int x, unsigned int y,
               Orientation orientation, unsigned int level, std::string teamName, PlayerTexture &playerTexture, sf::Color color)
        : APlayer(id, x, y, teamName),
          _playerTexture(playerTexture), _level(level), _orientation(orientation),
          _displayPosX(x), _displayPosY(y), _color(color)
{
    _angle = _orientation;

    setSpriteGrid(_playerTexture.getFormat("Idle"));
    setSprite({ genSprite(*_playerTexture.getTextVecPair("Idle").first.at(0)),
                genSprite(*_playerTexture.getTextVecPair("Idle").first.at(1)) });
    getSprite().first->setColor(_color);
}

bool Player::movement()
{
    if (abs(_displayPosY - _posY) > 2 || abs(_displayPosX - _posX) > 2)
        resetDisplayPos();

    if (std::clamp((double)_displayPosY, _posY - 0.3, _posY + 0.3) == _displayPosY
        && std::clamp((double)_displayPosX, _posX - 0.3, _posX + 0.3) == _displayPosX) {
        if (getAction() == WALK)
            setAction(IDLE);
        return false;
    }

    if (_displayPosY < _posY) {
        _orientation = SOUTH;
        _displayPosY += PLAYER_SPEED;
    }
    if (_displayPosY > _posY) {
        _orientation = NORTH;
        _displayPosY -= PLAYER_SPEED;
    }
    if (_displayPosX < _posX) {
        _orientation = EAST;
        _displayPosX += PLAYER_SPEED;
    }
    if (_displayPosX > _posX) {
        _orientation = WEST;
        _displayPosX -= PLAYER_SPEED;
    }

    setAction(WALK);
    return true;
}

void Player::update(int tileWidth, int tileHeight) {
    setSpriteGrid(_playerTexture.getFormat(actions[getAction()]));

    auto [x, y] = getRelativePos(tileWidth, tileHeight);
    const auto [sizeX, sizeY] = getSpriteSize();
    sf::IntRect rect(sizeX * PLAYER_SIZE, sizeY * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);

    _angle = _orientation * 4 - 2;
    _angle = std::clamp(_angle, 0, 15);

    movement();
    auto textVecs = _playerTexture.getTextVecPair(actions[getAction()]);

    updateSprite(x, y, rect, textVecs.first, *getSprite().first);
    updateSprite(x, y, rect, textVecs.second, *getSprite().second);

    updateFrame();
}

void Player::updateSprite(float x, float y, sf::IntRect rect, PlayerTexture::TextureVector &vector, sf::Sprite &sprite)
{
    _initialised = true;
    auto const &texture = *vector.at(_angle);

    sprite.setTextureRect(rect);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

Orientation Player::getOrientation() const
{
    return _orientation;
}

void Player::setLevel(unsigned int level)
{
    _level = level;
}

unsigned int Player::getLevel() const
{
    return _level;
}

void Player::setOrientation(Orientation orientation)
{
    _orientation = orientation;
}

bool Player::isInitialised() const
{
    return _initialised;
}
