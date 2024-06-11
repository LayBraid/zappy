#include "Display/Broadcast.hpp"

Broadcast::Broadcast(int x, int y, const sf::Color &color, int thickness)
{
    _circle.setFillColor(sf::Color::Transparent);
    _circle.setOutlineThickness(thickness);
    _circle.setOutlineColor(color);
    _circle.setRadius(1);
    _circle.setPosition(x, y);
}

bool Broadcast::addStep()
{
    if (step == 1300)
        return false;
    step++;
    _circle.setRadius(_circle.getRadius() + 0.5);
    _circle.setPosition(
    _circle.getPosition().x - 0.5, _circle.getPosition().y - 0.5);
    return true;
}

const sf::Shape &Broadcast::getShape() const
{
    return _circle;
}
