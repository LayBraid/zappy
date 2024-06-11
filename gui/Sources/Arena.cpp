#include "Arena.hpp"

Arena::Arena(int width, int height, std::shared_ptr<ResourceDrawer> resourceDrawer)
    : _width(width), _height(height), _resourceDrawer(resourceDrawer)
    // _grid(height, std::vector<std::shared_ptr<Tile>>(width))
{
    for (int i = 1; i <= 5; i++) {
        sf::Texture text;
        text.loadFromFile("gui/asset/Tiles/grass" + std::to_string(i) + ".png");
        _textures.push_back(text);
    }
    std::vector<sf::Color> colors{sf::Color::Red, sf::Color::Green};
    _grid = std::vector<std::vector<std::shared_ptr<Tile>>>();
    for (int y = 0; y < height; y++) {
        _grid.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int x = 0; x < width; x++) {
            _grid[y].push_back(std::make_shared<Tile>(_textures.at(rand() % _textures.size())));
            // std::cout << x << " " << y << std::endl;
            // std::cout << _grid[y][x]->getPosX() << " " << _grid[y][x]->getPosY() << std::endl;
            _grid[y][x]->setName(
            "Tile (" + std::to_string(x) + " " + std::to_string(y)+ ")");
            _grid[y][x]->setPos(x, y);
            _grid[y][x]->setColor(colors[(x+y)%2]);
        }
    }
}

void Arena::draw(sf::RenderWindow &window)
{
    for (auto &line : _grid) {
        for (auto &tile : line) {
            window.draw(tile->getSprite());
            _resourceDrawer->drawResources(window, tile);
        }
    }
}

int Arena::getWidth() const
{
    return _width;
}

int Arena::getHeight() const
{
    return _height;
}

int Arena::getTileWidth() const
{
    return _tileWidth;
}

int Arena::getTileHeight() const
{
    return _tileHeight;
}

std::shared_ptr<Tile> &Arena::getTile(int x, int y)
{
    return _grid[y][x];
}