#include "Objects/AObject.hpp"
#include "Arena.hpp"

AObject::AObject(const std::string &name, int posX, int posY, int food,
int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    : _name(name), _posX(posX), _posY(posY), _resources({linemate, deraumere, sibur, mendiane, phiras, thystame, food})
{
}

int AObject::getPosX() const
{
    return _posX;
}

int AObject::getPosY() const
{
    return _posY;
}

int AObject::getFood() const
{
    return _resources.at(FOOD);
}

int AObject::getLinemate() const
{
    return _resources.at(LINEMATE);
}

int AObject::getDeraumere() const
{
    return _resources.at(DERAUMERE);
}

int AObject::getSibur() const
{
    return _resources.at(SIBUR);
}

int AObject::getMendiane() const
{
    return _resources.at(MENDIANE);
}

int AObject::getPhiras() const
{
    return _resources.at(PHIRAS);
}

int AObject::getThystame() const
{
    return _resources.at(THYSTAME);
}

std::string AObject::getName() const
{
    return _name;
}

void AObject::setPosX(int posX)
{
    _posX = posX;
}

void AObject::setPosY(int posY)
{
    _posY = posY;
}

void AObject::setFood(int food)
{
    _resources.at(FOOD) = food;
}

void AObject::setLinemate(int linemate)
{
    _resources.at(LINEMATE) = linemate;
}

void AObject::setDeraumere(int deraumere)
{
    _resources.at(DERAUMERE) = deraumere;
}

void AObject::setSibur(int sibur)
{
    _resources.at(SIBUR) = sibur;
}

void AObject::setMendiane(int mendiane)
{
    _resources.at(MENDIANE) = mendiane;
}

void AObject::setPhiras(int phiras)
{
    _resources.at(PHIRAS) = phiras;
}

void AObject::setThystame(int thystame)
{
    _resources.at(THYSTAME) = thystame;
}

void AObject::setName(const std::string &name)
{
    _name = name;
}

void AObject::addPosX(int posX)
{
    _posX += posX;
}

void AObject::addPosY(int posY)
{
    _posY += posY;
}

void AObject::addFood(int food)
{
    _resources.at(FOOD) += food;
}

void AObject::addLinemate(int linemate)
{
    _resources.at(LINEMATE) += linemate;
}

void AObject::addDeraumere(int deraumere)
{
    _resources.at(DERAUMERE) += deraumere;
}

void AObject::addSibur(int sibur)
{
    _resources.at(SIBUR) += sibur;
}

void AObject::addMendiane(int mendiane)
{
    _resources.at(MENDIANE) += mendiane;
}

void AObject::addPhiras(int phiras)
{
    _resources.at(PHIRAS) += phiras;
}

void AObject::addThystame(int thystame)
{
    _resources.at(THYSTAME) += thystame;
}
