#include "Objects/Tile.hpp"
#include "Objects/ResourceDrawer.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <random>
#pragma once

class Arena
{
private:
    int _width;
    int _height;
    int _tileWidth = 130;
    int _tileHeight = 100;
    std::vector<std::vector<std::shared_ptr<Tile>>> _grid;
    std::vector<sf::Texture> _textures;
    std::shared_ptr<ResourceDrawer> _resourceDrawer;

public:
    Arena(int width, int height, std::shared_ptr<ResourceDrawer>);
    ~Arena() = default;

    void draw(sf::RenderWindow &window);

    int getWidth() const;
    int getHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;

    std::shared_ptr<Tile> &getTile(int x, int y);
};