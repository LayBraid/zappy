/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** PlayerTexture
*/

#include "Objects/Players/PlayerTexture.hpp"

PlayerTexture::PlayerTexture()
{
    for (auto &action : actions)
        _textures[action] = TextVecPair();
    for (auto &[key, val] : _textures) {
        std::string modePath = key + "/" + key;
        for (auto &path: paths) {
            loadTextures(val.first,  modePath + " Body " + path);
            loadTextures(val.second, modePath + " Shadow " + path);
        }
    }
}

void PlayerTexture::loadTextures(TextureVector &textures, std::string const &path)
{
    sf::Texture texture;
    texture.loadFromFile("gui/asset/Trantor1/" + path + ".png");
    textures.push_back(std::make_shared<sf::Texture>(texture));
}

PlayerTexture::TextVecPair &PlayerTexture::getTextVecPair(std::string key)
{
    return _textures[key];
}

std::pair<size_t, size_t> PlayerTexture::getFormat(std::string key) const
{
    return _textureFormats.at(key);
}
