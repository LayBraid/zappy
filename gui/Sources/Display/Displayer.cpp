#include "Display/Displayer.hpp"

Displayer::Displayer(Arena &arena, Players &players,
std::shared_ptr<ResourceDrawer> resourceDrawer, int screenWidth,
int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight), _arena(arena),
      _players(players), _clickedCoord{0, 0}, _animations()
{
    _window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(_screenWidth, _screenHeight), "Zappy");
    _view = std::make_shared<sf::View>();
    _view->reset(sf::FloatRect(0, 0, _screenWidth, _screenHeight));
    _window->setView(*_view);

    _hud = std::make_shared<HUD>(
    _window, resourceDrawer, _screenHeight, _screenWidth);
}

void Displayer::render(sf::Clock &clock, bool shouldUpdate)
{
    bool update = false;

    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asMilliseconds() > 100) {
        update = true;
        clock.restart();
    }

    _window->clear();
    _window->setView(*_view);

    _arena.draw(*_window);
    _players.draw(*_window, _arena.getTileWidth(), _arena.getTileHeight(), update);

    displayHUD(_objectOnMenu, shouldUpdate);
    _window->setView(*_view);

    auto i = std::begin(_animations);
    while (i != std::end(_animations)) {
        _window->draw((*i)->getShape());
        if (!(*i)->addStep()) {
            i = _animations.erase(i);
        } else {
            i++;
        }
    }

    _window->display();
}

bool Displayer::mouseClick(sf::Event &event)
{
    if (event.type != event.MouseButtonPressed ||
    event.mouseButton.button != sf::Mouse::Left)
        return false;

    bool clicked = false;

    sf::Vector2f pos =
    _window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    _clickedCoord = getMapCoords(pos);
    std::cout << "Clicked on : " << _clickedCoord.x << " " << _clickedCoord.y
              << std::endl;
    clicked = true;

    if (_clickedCoord.x < 0 || _clickedCoord.y < 0 ||
    _clickedCoord.x >= _arena.getWidth() ||
    _clickedCoord.y >= _arena.getHeight())
        _objectOnMenu = nullptr;
    else if (_players.isClicked(pos) != -1)
        _objectOnMenu = _players.getPlayer(_players.isClicked(pos));
    else
        _objectOnMenu = _arena.getTile(_clickedCoord.x, _clickedCoord.y);

    return clicked;
}

void Displayer::mouseScroll(sf::Event &event, std::map<int, float> &input)
{
    if (event.type != sf::Event::MouseWheelScrolled)
        return;

    auto button = event.mouseWheelScroll.delta;
    if (button == -1)
        input[sf::Keyboard::F] = 0.9;
    if (button == 1)
        input[sf::Keyboard::E] = 0.9;
}

bool Displayer::listenInput(std::map<int, float> &input)
{
    sf::Event event;
    bool clicked = false;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::KeyPressed)
            input[event.key.code] = 1.0;
        if (event.type == sf::Event::KeyReleased)
            input[event.key.code] = 0.99;
        clicked = mouseClick(event);
        mouseScroll(event, input);
    }
    return clicked;
}

void Displayer::displayHUD(std::shared_ptr<IObject> &object, bool askUpdate)
{
    _hud->displayInformationMenu(object);
    _hud->displayToasts();

    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(object);
    if (player == nullptr)
        return;
    _hud->displayPlayerInfo(player);
    if (askUpdate) {
        _commands += "ppo " + std::to_string(player->getPlayerId()) + "\n";
        _commands += "plv " + std::to_string(player->getPlayerId()) + "\n";
        _commands += "pin " + std::to_string(player->getPlayerId()) + "\n";
    }

    _window->setView(*_view);
}

sf::Vector2i Displayer::getMapCoords(const sf::Vector2f &coords)
{
    sf::Vector2i result;
    result.x =
    (coords.x / _arena.getTileWidth() + (coords.y / _arena.getTileHeight())) /
    2;
    result.y =
    (coords.y / _arena.getTileHeight() - (coords.x / _arena.getTileWidth())) /
    2;
    return result;
}

std::string Displayer::retrieveCommands()
{
    std::string result = _commands;
    _commands.clear();
    return result;
}

void Displayer::addAnimation(std::shared_ptr<IAnimation> &animation)
{
    for (unsigned int i = 0; i < _animations.size(); i++) {
        if (_animations[i]->getShape().getFillColor() ==
        animation->getShape().getFillColor()) {
            _animations.erase(_animations.begin() + i);
        }
    }
    _animations.push_back(animation);
}