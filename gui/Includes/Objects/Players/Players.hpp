#include "APlayer.hpp"
#include "PlayerTexture.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include <map>
#include <memory>

#pragma once

class Players
{
public:
    Players(/* args */);
    ~Players() = default;

    void addEgg(unsigned int id, unsigned int x, unsigned int y, std::string teamName);
    void addPlayer(std::shared_ptr<Player> player);
    void addPlayer(unsigned int id, unsigned int x, unsigned int y,
    Orientation orientation, unsigned int level, std::string teamName, sf::Color color);

    std::shared_ptr<Player> getPlayer(int id);
    std::shared_ptr<Egg> getEgg(int id);

    void removePlayer(unsigned int id);
    void removeEgg(unsigned int id);
    
    int isClicked(const sf::Vector2f &mousePos);

    void draw(sf::RenderWindow &window, int tileWidth, int tileHeight, bool update);

private:
    std::map<int, std::shared_ptr<Player>> _players;
    std::map<int, std::shared_ptr<Egg>> _eggs;
    PlayerTexture _playerTexture;
};
