#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include "Arena.hpp"
#include "Objects/Players/Players.hpp"
#include "Broadcast.hpp"
#include "HUD.hpp"

#pragma once

class Displayer
{
private:
    int _screenWidth;
    int _screenHeight;

    Arena &_arena;
    Players &_players;
    std::vector<sf::ConvexShape> _grid;

    std::shared_ptr<HUD> _hud;
    std::shared_ptr<sf::RenderWindow> _window;
    std::shared_ptr<sf::View> _view;

    sf::Vector2i _clickedCoord;

    std::string _commands;

    // This a test, it will be removed

    std::shared_ptr<IObject> _objectOnMenu = nullptr;
    std::vector<std::shared_ptr<IAnimation>> _animations;

public:
    Displayer(Arena &arena, Players &players, std::shared_ptr<ResourceDrawer> resourceDrawer,
              int screenWidth = 1080, int screenHeight = 720);
    ~Displayer() = default;

    bool isOpen() const { return _window->isOpen(); };
    void render(sf::Clock &clock, bool shouldUpdate);
    bool listenInput(std::map<int, float> &input);

    /**
     * This methods contains the logic for zooming
     * @param event
     * @param input
     */
    void mouseScroll(sf::Event &event, std::map<int, float> &input);

    /**
     * This method contains the logic for opening the information box
     * @param event
     * @return whether or not something was clicked
     */
    bool mouseClick(sf::Event &event);

    /**
     * This method draws the HUD
     * @param object
     * @param askUpdate
     */
    void displayHUD(std::shared_ptr<IObject> &object, bool askUpdate = false);

    std::shared_ptr<HUD> getHUD() const
    {
        return _hud;
    };

    std::shared_ptr<sf::RenderWindow> getWindow() const
    {
        return _window;
    };

    std::shared_ptr<sf::View> getView() const
    {
        return _view;
    };

    sf::Vector2i getMapCoords(const sf::Vector2f &);

    std::string retrieveCommands();

    void addAnimation(std::shared_ptr<IAnimation> &);
};