#include "IAnimation.hpp"

#pragma once

class Broadcast : public IAnimation
{

private:
    sf::CircleShape _circle;
    int step = 0;

public:
    Broadcast(int x, int y, const sf::Color &color, int thickness);
    ~Broadcast() = default;

    bool addStep() final;
    const sf::Shape &getShape() const final;

};
