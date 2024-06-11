#include <SFML/Graphics.hpp>
#include <memory>

#pragma once

class IAnimation
{
public:
    ~IAnimation() = default;

    virtual bool addStep() = 0;

    virtual const sf::Shape &getShape() const = 0;
};