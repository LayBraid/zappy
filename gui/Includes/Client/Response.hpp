/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.dury
** File description:
** Response
*/

#pragma once

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

/**
 * The list of valid commands
 */
const std::vector<std::string> validCommands =
{
    "msz",
    "bct",
    "bct",
    "tna",
    "pnw",
    "ppo",
    "plv",
    "pin",
    "pex",
    "pbc",
    "pic",
    "pie",
    "pfk",
    "pdr",
    "pgt",
    "pdi",
    "enw",
    "ebo",
    "edi",
    "sgt",
    "sst",
    "seg",
    "smg",
    "suc",
    "sbp",
    "eht",
};

/**
 * This class allows to separate the command's name from its values
 */
class Response {
public:
    explicit Response(std::string_view const &raw): _label(raw.substr(0, 3)),
                                                    _value(raw.substr(4, raw.size() - 4))
    {
        if (std::find(validCommands.begin(), validCommands.end(), _label) == validCommands.end()) {
            throw ClientException("Invalid command name: " + _label);
        }
    };
    ~Response() = default;

    [[nodiscard]] std::string getLabel() const { return _label; };
    [[nodiscard]] std::string getValue() const { return _value; };

    /**
     * This method fills a value vector from all the values inside the initial string
     * @return the value vector
     */
    std::vector<std::string> getValueVector()
    {
        std::stringstream ss(_value);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> values(begin, end);
        return values;
    }

private:
    std::string _label;
    std::string _value;

};