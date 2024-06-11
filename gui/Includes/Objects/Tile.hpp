#include "AObject.hpp"
#include <SFML/Graphics.hpp>

#pragma once

class Tile : public AObject
{
private:
    int _tileWidth = 130;
    int _tileHeight = 100;

    sf::Sprite _sprite;

    void buildTile();

public:
    explicit Tile(sf::Texture &texture);
    ~Tile() = default;

    const sf::Sprite &getSprite() const
    {
        return _sprite;
    }

    const std::vector<int> &getResources() const
    {
        return _resources;
    }

    std::pair<int, int> getSize() const
    { 
        return { _tileWidth, _tileHeight };
    };

    void setPos(int x, int y);
    void setPosX(int x) final;
    void setPosY(int y) final;
    void addPosX(int x) final;
    void addPosY(int y) final;
    void setColor(const sf::Color &color);

    void setTileWidth(int width);
    void setTileHeight(int height);

};