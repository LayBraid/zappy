#include "Objects/AObject.hpp"
#include "Objects/Players/PlayerTexture.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <iostream>

#pragma once

#define DEBUG_MODE  false
#define PLAYER_SPEED 0.3
enum Action { IDLE, WALK, SHOUT, HATCHING, DEAD, JUMP };

class APlayer : public AObject
{
public:
    using SpritePair = std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Sprite>>;

    APlayer(unsigned int id, unsigned int x, unsigned int y, std::string teamName);
    ~APlayer() = default;

    std::shared_ptr<sf::Sprite> genSprite(sf::Texture &texture);
    void setTeamColor(sf::Color color) { _teamColor = color; };
    std::string getTeamName() const;
    unsigned int getPlayerId() const;
    sf::Color getColor() const;

    virtual void update(int tileWidth, int tileHeight) = 0;
    void updateFrame();
    Action getAction() const;
    void setAction(Action action);
    [[nodiscard]] std::pair<size_t, size_t> getSpriteSize() const;
    void setSprite(SpritePair sprite);
    SpritePair getSprite() const;

    std::pair<size_t, size_t> getSpriteGrid() const;
    void setSpriteGrid(std::pair<size_t, size_t> sizes);

    void setDecal(int x, int y);
    bool isClicked(sf::Vector2f mousePos);

    virtual void resetDisplayPos() = 0;
    virtual std::pair<float, float> getDisplayPos() = 0;
    std::pair<float, float> getRelativePos(int tileWidth, int tileHeight);
    void setPosX(int x) final;
    void setPosY(int y) final;
    void addPosX(int x) final;
    void addPosY(int y) final;

private:
    sf::Color _teamColor;
    std::string _teamName;

    unsigned int _playerId;

    int _decalX = 0; // For the displayer
    int _decalY = 0; // For the displayer

    Action _action = IDLE;
    std::chrono::time_point<std::chrono::steady_clock> _animStart;
    SpritePair _sprite;
    size_t _cols = 0;
    size_t _rows = 0;
    size_t _animIndex = 0;
};
