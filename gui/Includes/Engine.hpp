#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <iostream>
#include <mutex>
#include "Types.hpp"
#include "Display/Displayer.hpp"
#include "Client/Client.hpp"

#pragma once

enum Axis { X, Y, Z };

#define COOLDOWN        0.0005
#define SPEED           0.18
#define RESPONSE(label, func) { label, [this](StringVector &value) { func(value); } }
#define INTERPRET_RES() _responses[res.getLabel()](res.getValueVector())
#define GET_INT(index)  stoi(values.at(index))

const static std::vector<sf::Keyboard::Key> quantifiedInput = {
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Left,
        sf::Keyboard::Right,
        sf::Keyboard::E,
        sf::Keyboard::F,
};

class Engine
{

using StringVector = const std::vector<std::string> &;
using Command = std::function<void(StringVector)>;
using CommandsMap = std::map<std::string, Command>;

private:
    std::map<int, float> _input;
    std::shared_ptr<Arena> _arena;
    std::shared_ptr<Displayer> _window;
    IClient &_client;
    CommandsMap _responses;
    std::map<std::string, std::string> _parameters;
    std::map<std::string, sf::Color> _teams;
    Players _players;
    size_t _timeUnit;
    sf::Clock _clock;
    std::atomic_bool _open = true;

public:
    explicit Engine(IClient &client);
    ~Engine() = default;

    [[nodiscard]] std::shared_ptr<Displayer> getWindow() const;

    void cameraMovement(Axis axis, double force);

    void getResponse();

    /**
     * Map size\n
     * "msz X Y"\n
     * @param X: width or horizontal position
     * @param Y: height or vertical position
     */
    void msz(StringVector values);

    /**
     * Content of a tile\n
     * "bct X Y"\n
     * @param X: width or horizontal position
     * @param Y: height or vertical position
     */
    void bct(StringVector values);

    /**
     * Name of a team\n
     * "tna N"\n
     * @param N: name of the team
     */
    void tna(StringVector values);

    /**
     * connection of a new player\n
     * "pnw #n X Y O L N"\n
     * @param n: player number
     * @param X: width or horizontal position
     * @param Y: height or vertical position
     * @param O: orientation: 1(N), 2(E), 3(s), 4(W)
     * @param L: player level
     * @param N: name of the team
     */
    void pnw(StringVector values);

    /**
     * player's position
     * "ppo n X Y O"
     * @param n: id
     * @param X: width or horizontal position
     * @param Y: height or vertical position
     * @param O: orientation: 1(N), 2(E), 3(s), 4(W)
     */
     void ppo(StringVector values);

    /**
    * player's level
    * "plv n L"
    * @param n: id
    * @param L: level
    */
    void plv(StringVector values);

    /**
    * player's inventory
    * "pin n X Y q0 q1 q2 q3 q4 q5 q6"
    * @param n: id
    * @param X: width or horizontal position
    * @param Y: height or vertical position
    */
    void pin(StringVector values);

    /**
    * expulsion
    * "pex n"
    * @param n: id
    */
    void pex(StringVector values);

    /**
    * broadcast
    * "pbc n M"
    * @param n: id
    * @param M: message
    */
    void pbc(StringVector values);

    /**
    * start of an incantation
    * "pic X Y L n n ..."
    * @param n: id
    * @param X: width or horizontal position
    * @param Y: height or vertical position
    * @param L: level
    * @param n: id
    */
    void pic(StringVector values);

    /**
    * end of an incantation
    * "pie X Y R"
    * @param n: id
    * @param X: width or horizontal position
    * @param Y: height or vertical position
    * @param R: incantation result
    */
    void pie(StringVector values);

    /**
    * egg laying by the player
    * "pfk n"
    * @param n: id
    */
    void pfk(StringVector values);

    /**
    * resource dropping
    * "pdr n i"
    * @param n: player id
    * @param i: resource id
    */
    void pdr(StringVector values);

    /**
    * resource collecting
    * "pgt n i"
    * @param n: player id
    * @param i: resource id
    */
    void pgt(StringVector values);

    /**
    * death of a player
    * "pdi n"
    * @param n: player id
    */
    void pdi(StringVector values);

    /**
    * an egg was laid by a player
    * "enw e n X Y"
    * @param e: egg id
    * @param n: player id
    * @param X: width or horizontal position
    * @param Y: height or vertical position
    */
    void enw(StringVector values);

    /**
    * player connection for an egg
    * "ebo e"
    * @param e: egg id
    */
    void ebo(StringVector values);

    /**
    * death of an egg
    * "edi e"
    * @param e: egg id
    */
    void edi(StringVector values);

    /**
     * Time unit request\n
     * "sgt T"\n
     * @param T: time unit
     */
    void sgt(StringVector values);

    /**
     * Time unit modification\n
     * "sst T"\n
     * @param T: time unit
     */
    void sst(StringVector values);

    /**
     * end of game\n
     * "seg N"\n
     * @param N: name of the team
     */
    void seg(StringVector values);

    /**
     * Message from the server\n
     * "smg M"\n
     * @param M: message
     */
    void smg(StringVector values);

    /**
     * Unknown command\n
     * "suc"\n
     */
    void suc(StringVector values);

    /**
     * Command parameter\n
     * "sbp"\n
     */
    void sbp(StringVector values);

    void update();
    void listen();
    void render();
    void run();

    Orientation getOrientation(int orientation)
    {
        switch (orientation) {
            case 0: return NORTH;
            case 1: return EAST;
            case 2: return SOUTH;
            case 3: return WEST;
        }
    }
};