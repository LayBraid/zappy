#include "IObject.hpp"
#include <algorithm>
#include <string>
#include <vector>

#pragma once

enum Resource {LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME, FOOD};

class AObject : public IObject
{
protected:
    std::string _name;

    int _posX;
    int _posY;

    std::vector<int> _resources;

public:
    AObject(const std::string &name,
    int posX = 0, int posY = 0, int food = 0, int linemate = 0,
    int deraumere = 0, int sibur = 0, int mendiane = 0, int phiras = 0,
    int thystame = 0);
    ~AObject() = default;

    int getPosX() const final;
    int getPosY() const final;
    int getFood() const final;
    int getLinemate() const final;
    int getDeraumere() const final;
    int getSibur() const final;
    int getMendiane() const final;
    int getPhiras() const final;
    int getThystame() const final;
    std::string getName() const final;

    void setPosX(int posX) override; // Override by Tile
    void setPosY(int posY) override; // Override by Tile
    void setFood(int food) final;
    void setLinemate(int linemate) final;
    void setDeraumere(int deraumere) final;
    void setSibur(int sibur) final;
    void setMendiane(int mendiane) final;
    void setPhiras(int phiras) final;
    void setThystame(int thystame) final;
    void setName(const std::string &name) final;

    void addPosX(int posX) override; // Override by Tile
    void addPosY(int posY) override; // Override by Tile
    void addFood(int food) final;
    void addLinemate(int linemate) final;
    void addDeraumere(int deraumere) final;
    void addSibur(int sibur) final;
    void addMendiane(int mendiane) final;
    void addPhiras(int phiras) final;
    void addThystame(int thystame) final;
};