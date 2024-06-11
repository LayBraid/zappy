#include "Objects/Players/APlayer.hpp"

APlayer::APlayer(unsigned int id, unsigned int x, unsigned int y, std::string teamName)
        : AObject(teamName + " : " + std::to_string(id), x, y),
        _teamName(teamName), _playerId(id)
{
    setTeamColor(sf::Color::Blue); // TODO: change this
    _animStart = std::chrono::steady_clock::now();
}

std::shared_ptr<sf::Sprite> APlayer::genSprite(sf::Texture &texture)
{
    sf::Sprite sprite;
    sprite.setOrigin(256 / 2.0, 256 / 4.0);
    sprite.setTexture(texture);
    return std::make_shared<sf::Sprite>(sprite);
}

std::string APlayer::getTeamName() const
{
    return _teamName;
}

unsigned int APlayer::getPlayerId() const
{
    return _playerId;
}

void APlayer::setDecal(int x, int y)
{
    _decalX = x;
    _decalY = y;
}

bool APlayer::isClicked(sf::Vector2f mousePos)
{
    return getSprite().first->getGlobalBounds().contains(mousePos.x, mousePos.y);
}

std::pair<size_t, size_t> APlayer::getSpriteSize() const
{
    auto [cols, rows] = getSpriteGrid();
    size_t x = _animIndex % cols;
    size_t y = _animIndex % rows;
    return { x, y };
}

APlayer::SpritePair APlayer::getSprite() const
{
    return {_sprite.first, _sprite.second};
}

void APlayer::updateFrame()
{
    _animIndex = (_animIndex + 1) % (_rows * _cols);
    if (_action == WALK || _action == JUMP) return;
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = duration_cast<std::chrono::duration<double>>(t1 - _animStart);
    if (time_span.count() > 1)
        setAction(IDLE);
}

void APlayer::setPosX(int x)
{
    _posX = x;
}

void APlayer::setPosY(int y)
{
    _posY = y;
}

void APlayer::addPosX(int x)
{
    _posX += x;
}

void APlayer::addPosY(int y)
{
    _posY += y;
}

void APlayer::setSpriteGrid(std::pair<size_t, size_t> sizes)
{
    _cols = sizes.first;
    _rows = sizes.second;
}

void APlayer::setSprite(APlayer::SpritePair sprite)
{
    _sprite = sprite;
}

void APlayer::setAction(Action action)
{
    _animStart = std::chrono::steady_clock::now();
    _action = action;
}

std::pair<float, float> APlayer::getRelativePos(int tileWidth, int tileHeight)
{
    auto [displayX, displayY] = getDisplayPos();

    float x = (displayX - displayY) * tileWidth + _decalX;
    float y = (displayY + displayX) * tileHeight + _decalY;

    return {x, y};
}

Action APlayer::getAction() const
{
    return _action;
}

std::pair<size_t, size_t> APlayer::getSpriteGrid() const
{
    return { _cols, _rows };
}

sf::Color APlayer::getColor() const {
    return _teamColor;
}