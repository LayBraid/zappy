#include "Objects/Tile.hpp"

Tile::Tile(sf::Texture &texture) : AObject("")
{
    _sprite.setTexture(texture);
    _sprite.setScale(2,2);
    _sprite.setOrigin(_tileWidth / 2, 0);
    buildTile();
}

void Tile::buildTile()
{
    _sprite.setPosition((_posX - _posY) * _tileWidth, (_posX + _posY) * _tileHeight);
}

void Tile::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
    buildTile();
}

void Tile::setPosX(int x)
{
    AObject::setPosX(x);
    buildTile();
}

void Tile::setPosY(int y)
{
    AObject::setPosY(y);
    buildTile();
}

void Tile::setColor(const sf::Color &color)
{
//    _tile.setFillColor(color);
}

void Tile::setTileWidth(int width)
{
    _tileWidth = width;
    buildTile();
}

void Tile::setTileHeight(int height)
{
    _tileHeight = height;
    buildTile();
}

void Tile::addPosX(int x)
{
    AObject::addPosX(x);
    buildTile();
}

void Tile::addPosY(int y)
{
    AObject::addPosY(y);
    buildTile();
}
