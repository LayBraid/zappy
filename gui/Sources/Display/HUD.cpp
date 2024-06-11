/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** HUD
*/

#include "Display/HUD.hpp"

HUD::HUD(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<ResourceDrawer> resourceDrawer,
         int screenWidth, int screenHeight) : _resourceDrawer(resourceDrawer), _window(window),
         _screenHeight(screenHeight), _screenWidth(screenWidth)
{
    _font.loadFromFile("gui/asset/ROBOTO.TTF");
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(26);
    _texture.loadFromFile("gui/asset/HUD.png");
    _infoMenu.setTexture(_texture);

    _infoMenu.setScale(screenWidth / _texture.getSize().x, (screenHeight * 0.2) / _texture.getSize().y);

    _view.reset(sf::FloatRect(0, 0, _screenWidth, _screenHeight));

    _offsetY = -220;
    _offsetX = 0;
}

void HUD::displayPlayerInfo(std::shared_ptr<Player> &player)
{
    _text.setPosition(60, _offsetY + 40);
    _text.setString("Level: " + std::to_string(player->getLevel()));
    _window->draw(_text);
}

void HUD::displayResourceInfo(std::array<int, 7> quantity)
{
    for (_offsetX = 0; _offsetX < 7; _offsetX++) {
        auto itemSprite = _resourceDrawer->getItemSprite(static_cast<Resource>(_offsetX));
        itemSprite.setPosition(200 + 70 * _offsetX, _offsetY + 15);
        _window->draw(itemSprite);

        _text.setString("x" + std::to_string(quantity[_offsetX]));
        _text.setPosition(200 + 70 * _offsetX, _offsetY - 15);
        _window->draw(_text);
    }
}

void HUD::displayInformationMenu(std::shared_ptr<IObject> &object)
{
    _window->setView(_view);
    _infoMenu.setPosition(20, _offsetY);
    _window->draw(_infoMenu);
    if (!object) {
        if (_offsetY > -210) _offsetY -= 0.5;
        return;
    }
    if (_offsetY < 0) _offsetY += 0.5;

    _offsetY += 80;

    _text.setString(object->getName());
    _text.setPosition(60, _offsetY);
    _window->draw(_text);

    std::array<int, 7> quantity = {
            object->getLinemate(), object->getDeraumere(),
            object->getSibur(), object->getMendiane(), object->getPhiras(),
            object->getThystame(), object->getFood()
    };
    displayResourceInfo(quantity);
    _offsetY -= 80;
}

void HUD::addToast(std::string message)
{
    auto toast = std::make_shared<Toast>(message, _font, _texture, _screenHeight);
    _toasts.push_back(toast);
    if (_toasts.size() > 3) _toasts.erase(_toasts.begin());
}

void HUD::displayToasts()
{
    int i = 0;
    for (auto iter = _toasts.begin(); iter < _toasts.end(); iter++, i++) {
        auto [text, sprite] = (*iter)->getDrawables();
        _window->draw(sprite);
        _window->draw(text);
        if ((*iter)->update(i)) _toasts.erase(iter);
    }
}
