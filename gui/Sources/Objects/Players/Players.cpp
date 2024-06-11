#include <iostream>
#include "Objects/Players/Players.hpp"
#include "Objects/Players/Egg.hpp"

Players::Players(/* args */) = default;

void Players::addPlayer(std::shared_ptr<Player> player)
{
    _players[player->getPlayerId()] = player;
}

void Players::addEgg(unsigned int id, unsigned int x, unsigned int y, std::string teamName)
{
    std::cout << x << ":" << y << std::endl;
    auto egg = Egg(id, x, y, teamName);
    egg.setAction(HATCHING);
    _eggs[id] = std::make_shared<Egg>(egg);
}

void Players::addPlayer(unsigned int id, unsigned int x, unsigned int y,
Orientation orientation, unsigned int level, std::string teamName, sf::Color color)
{
    auto player = Player(id, x, y, orientation, level, teamName, _playerTexture, color);
    _players[id] = std::make_shared<Player>(player);
}

std::shared_ptr<Player> Players::getPlayer(int id)
{
    return _players.at(id);
}

std::shared_ptr<Egg> Players::getEgg(int id)
{
    return _eggs.at(id);
}

void Players::removePlayer(unsigned int id)
{
    _players.erase(id);
}

void Players::removeEgg(unsigned int id)
{
    _eggs.erase(id);
}

int Players::isClicked(const sf::Vector2f &mousePos)
{
    for (auto &player : _players) {
        if (player.second->isClicked(mousePos))
            return player.first;
    }
    return -1;
}

void Players::draw(sf::RenderWindow &window, int tileWidth, int tileHeight, bool update)
{
    for (auto const &egg : _eggs) {
        if (update) egg.second->update(tileWidth, tileHeight);
        window.draw(*egg.second->getSprite().second);
        window.draw(*egg.second->getSprite().first);
    }
    for (auto const &player : _players) {
        if (update) player.second->update(tileWidth, tileHeight);
        if (!player.second->isInitialised()) continue;
        window.draw(*player.second->getSprite().second);
        window.draw(*player.second->getSprite().first);
    }
}
