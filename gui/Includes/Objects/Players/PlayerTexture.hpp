/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** PlayerTexture
*/

#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include "Constants.hpp"

static const std::vector<std::string> paths = {
        "0",
        "022",
        "045",
        "067",
        "090",
        "112",
        "135",
        "157",
        "180",
        "202",
        "225",
        "247",
        "270",
        "292",
        "315",
        "337"
};
static const std::vector<std::string> actions = {
        "Idle",
        "Walk",
        "Shout",
        "Attack1",
        "Death",
        "Jump"
};

class PlayerTexture {
public:
    using TextureVector = std::vector<std::shared_ptr<sf::Texture>>;
    using TextVecPair = std::pair<TextureVector, TextureVector>;
    using TextureMap = std::map<std::string, TextVecPair>;

    PlayerTexture();
    ~PlayerTexture() = default;

    void loadTextures(TextureVector &textures, std::string const &path);
    TextVecPair &getTextVecPair(std::string key);
    std::pair<size_t, size_t> getFormat(std::string key) const;

private:
    TextureMap _textures;
    std::map<std::string, std::pair<size_t, size_t>> _textureFormats = {
            {"Idle", { 4, 5 }},
            {"Walk", { 4, 4 }},
            {"Shout", { 6, 4 }},
            {"Attack1", { 6, 4 }},
            {"Death", { 4, 4 }},
            {"Jump", { 6, 4 }},
    };
};
