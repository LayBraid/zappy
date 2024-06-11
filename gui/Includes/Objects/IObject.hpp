#include <string>

#pragma once

class IObject
{
public:
    ~IObject() = default;

    virtual int getPosX() const = 0;
    virtual int getPosY() const = 0;
    virtual int getFood() const = 0;
    virtual int getLinemate() const = 0;
    virtual int getDeraumere() const = 0;
    virtual int getSibur() const = 0;
    virtual int getMendiane() const = 0;
    virtual int getPhiras() const = 0;
    virtual int getThystame() const = 0;
    virtual std::string getName() const = 0;
    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setFood(int food) = 0;
    virtual void setLinemate(int linemate) = 0;
    virtual void setDeraumere(int deraumere) = 0;
    virtual void setSibur(int sibur) = 0;
    virtual void setMendiane(int mendiane) = 0;
    virtual void setPhiras(int phiras) = 0;
    virtual void setThystame(int thystame) = 0;
    virtual void setName(const std::string &name) = 0;
    virtual void addPosX(int posX) = 0;
    virtual void addPosY(int posY) = 0;
    virtual void addFood(int food) = 0;
    virtual void addLinemate(int linemate) = 0;
    virtual void addDeraumere(int deraumere) = 0;
    virtual void addSibur(int sibur) = 0;
    virtual void addMendiane(int mendiane) = 0;
    virtual void addPhiras(int phiras) = 0;
    virtual void addThystame(int thystame) = 0;
};