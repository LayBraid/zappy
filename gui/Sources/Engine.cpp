#include "Engine.hpp"

Engine::Engine(IClient &client) : _client(client)
{
    _input = {
            {sf::Keyboard::Up, 0.0},
            {sf::Keyboard::Down, 0.0},
            {sf::Keyboard::Left, 0.0},
            {sf::Keyboard::Right, 0.0},
    };
    _responses = {
            RESPONSE("msz", msz),
            RESPONSE("bct", bct),
            RESPONSE("tna", tna),
            RESPONSE("pnw", pnw),
            RESPONSE("ppo", ppo),
            RESPONSE("plv", plv),
            RESPONSE("pin", pin),
            RESPONSE("pex", pex),
            RESPONSE("pbc", pbc),
            RESPONSE("pic", pic),
            RESPONSE("pie", pie),
            RESPONSE("pfk", pfk),
            RESPONSE("pdr", pdr),
            RESPONSE("pgt", pgt),
            RESPONSE("pdi", pdi),
            RESPONSE("enw", enw),
            RESPONSE("ebo", ebo),
            RESPONSE("edi", edi),
            RESPONSE("sgt", sgt),
            RESPONSE("sst", sst),
            RESPONSE("seg", seg),
            RESPONSE("smg", smg),
            RESPONSE("suc", suc),
    };
}

void Engine::cameraMovement(Axis axis, double force)
{
    float zoomValue = _window->getView()->getSize().x / 1080;
    switch (axis) {
    case X: _window->getView()->move(force * zoomValue, 0); break;
    case Y: _window->getView()->move(0, force * zoomValue); break;
    case Z: _window->getView()->zoom(1 + force / 400); break;
    }
}

void Engine::update()
{
    for (auto const &[key, val] : _input) {
        if (val <= 0)
            continue;
        auto movement = val * SPEED;
        switch (key) {
        case sf::Keyboard::Up: cameraMovement(Y, -movement); break;
        case sf::Keyboard::Down: cameraMovement(Y, movement); break;
        case sf::Keyboard::Left: cameraMovement(X, -movement); break;
        case sf::Keyboard::Right: cameraMovement(X, movement); break;
        case sf::Keyboard::E: cameraMovement(Z, -movement); break;
        case sf::Keyboard::F: cameraMovement(Z, movement); break;
        case sf::Keyboard::Escape: getWindow()->getWindow()->close(); break;
        default: break;
        }

        bool isQuantified =
        std::find(quantifiedInput.begin(), quantifiedInput.end(), key) !=
        quantifiedInput.end();
        if (!isQuantified)
            _input[key] = 0;
        if (val < 1.0)
            _input[key] -= COOLDOWN;
    }
}

void Engine::render()
{
    _clock.restart();
    while (true) {
        try {
            getResponse();
        } catch (ClientException &e) {
            std::cerr << e.what() << std::endl;
        }
        auto window = getWindow();
        if (!window)
            continue;
        update();
        bool clicked = window->listenInput(_input);
        window->render(_clock, clicked);
        _open = window->isOpen();
        if (!_open)
            break;
        _client.setCommand(getWindow()->retrieveCommands());
    }
}

void Engine::listen()
{
    while (true) {
        _client.listen();
        if (!_open)
            break;
    }
}

void Engine::run()
{
    auto comm = std::thread(&Engine::listen, this);
    comm.detach();

    render();
}

void Engine::getResponse()
{
    std::string cmd = _client.getBuffer().getNextCommand();
    if (cmd.empty() || std::find(cmd.begin(), cmd.end(), ' ') == cmd.end())
        return;
    auto res = Response(cmd);
    try {
        std::cout << res.getLabel() << ": ";
        for (auto &i : res.getValueVector()) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        INTERPRET_RES();
    } catch (std::bad_function_call &) {
        std::cerr << "Command " << res.getLabel() << " is not implemented."
                  << std::endl;
    }
}

std::shared_ptr<Displayer> Engine::getWindow() const
{
    return _window;
}

void Engine::msz(StringVector values)
{
    std::string x = values.at(0);
    std::string y = values.at(1);
    _parameters["mszX"] = x;
    _parameters["mszY"] = y;

    if (!getWindow()) {
        auto resourceDrawer = std::make_shared<ResourceDrawer>();
        _arena = std::make_shared<Arena>(stoi(x), stoi(y), resourceDrawer);
        _window = std::make_shared<Displayer>(*_arena, _players, resourceDrawer);
    }
}

void Engine::bct(StringVector values)
{
    int x = GET_INT(0);
    int y = GET_INT(1);

    auto tile = _arena->getTile(x, y);
    tile->setFood(GET_INT(2));
    tile->setLinemate(GET_INT(3));
    tile->setDeraumere(GET_INT(4));
    tile->setSibur(GET_INT(5));
    tile->setMendiane(GET_INT(6));
    tile->setPhiras(GET_INT(7));
    tile->setThystame(GET_INT(8));
}

void Engine::tna(StringVector values)
{
    auto const &teamName = values.at(0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    auto color = sf::Color(dis(gen), dis(gen), dis(gen));

    _teams[teamName] = color;
}

void Engine::pnw(StringVector values)
{
    int id = GET_INT(0);
    int x = GET_INT(1);
    int y = GET_INT(2);
    auto orientation = getOrientation(GET_INT(3));
    int level = GET_INT(4);
    std::string team = values.at(5);

    _players.addPlayer(id, x, y, orientation, level, team, _teams.at(team));
}

void Engine::ppo(StringVector values)
{
    int id = GET_INT(0);
    int x = GET_INT(1);
    int y = GET_INT(2);
    auto orientation = static_cast<Orientation>(GET_INT(3));

    auto player = _players.getPlayer(id);
    player->setPosX(x);
    player->setPosY(y);
    player->setOrientation(orientation);
}

void Engine::plv(StringVector values)
{
    auto player = _players.getPlayer(GET_INT(0));
    unsigned int level = GET_INT(1);

    if (player->getLevel() == level) return;

    player->setAction(IDLE);

    float xDisplay = (player->getPosX() - player->getPosY()) * _arena->getTileWidth();
    float yDisplay = (player->getPosY() + player->getPosX()) * _arena->getTileHeight();

    std::shared_ptr<IAnimation> anim = std::make_shared<Broadcast>(
            xDisplay,
            yDisplay,
            sf::Color::Magenta, level + 3
    );
    _window->addAnimation(anim);
    _window->getHUD()->addToast("New level: " + std::to_string(level));
    player->setLevel(level);
}

void Engine::pin(StringVector values)
{
    auto player = _players.getPlayer(GET_INT(0));
    player->setPosX(GET_INT(1));
    player->setPosY(GET_INT(2));
    player->setFood(GET_INT(2));
    player->setLinemate(GET_INT(3));
    player->setDeraumere(GET_INT(4));
    player->setSibur(GET_INT(5));
    player->setMendiane(GET_INT(6));
    player->setPhiras(GET_INT(7));
    player->setThystame(GET_INT(8));
}

void Engine::pex(StringVector values)
{
    _players.getPlayer(GET_INT(0))->setAction(DEAD);
}

void Engine::pbc(StringVector values)
{
    auto player = _players.getPlayer(GET_INT(0));
    sf::Vector2f re = player->getSprite().first->getPosition();
    std::shared_ptr<IAnimation> anim = std::make_shared<Broadcast>(re.x, re.y, player->getColor(), 3);
    _window->addAnimation(anim);
}

void Engine::pic(StringVector values)
{
    int x = GET_INT(0);
    int y = GET_INT(1);
    int level = GET_INT(2);

    for (int i = 3; i < values.size(); i++) {
        auto player = _players.getPlayer(GET_INT(i));
        player->setAction(JUMP);

        float xDisplay = (x - y) * _arena->getTileWidth();
        float yDisplay = (y + x) * _arena->getTileHeight();

        std::shared_ptr<IAnimation> anim = std::make_shared<Broadcast>(
                xDisplay,
                yDisplay,
                sf::Color::Magenta,level + 3
        );
        _window->addAnimation(anim);
    }
}

void Engine::pie(StringVector values)
{
    const std::string &r = values.at(2);

    _window->getHUD()->addToast("Incantation finished: " + r);
}

void Engine::pfk(StringVector values)
{
    int id = GET_INT(0);
    _players.getPlayer(id)->setAction(SHOUT);
}

void Engine::pdr(StringVector values)
{
    int id = GET_INT(0);
    int resource = GET_INT(1);

    if (_timeUnit <= 10) _window->getHUD()->addToast("Dropped " + resources.at(resource));
    _players.getPlayer(id)->setAction(SHOUT);
}

void Engine::pgt(StringVector values)
{
    int id = GET_INT(0);
    int resource = GET_INT(1);

    if (_timeUnit <= 10) _window->getHUD()->addToast("Collected " + resources.at(resource));
    _players.getPlayer(id)->setAction(SHOUT);
}

void Engine::pdi(StringVector values)
{
    int id = GET_INT(0);
    _players.removePlayer(id);
}

void Engine::enw(StringVector values)
{
    int eggId = GET_INT(0);
    int playerId = GET_INT(1);
    int X = GET_INT(2);
    int Y = GET_INT(3);

    _players.getPlayer(playerId)->setAction(SHOUT);
    _players.addEgg(eggId, X, Y, _players.getPlayer(playerId)->getTeamName());
}

void Engine::ebo(StringVector values)
{
    _players.removeEgg(GET_INT(0));
}

void Engine::edi(StringVector values)
{
    _players.removeEgg(GET_INT(0));
}

void Engine::sgt(StringVector values)
{
    _timeUnit = GET_INT(0);
}

void Engine::sst(StringVector values)
{
    _timeUnit = GET_INT(0);
}

void Engine::seg(StringVector values)
{
    std::string winner = values.at(0);
    _window->getHUD()->addToast("Winner: " + winner);
}

void Engine::smg(StringVector values)
{
    std::string msg = values.at(0);
    _window->getHUD()->addToast("Message: " + msg);
}

void Engine::suc(StringVector values)
{
    std::string msg = values.at(0);
    _window->getHUD()->addToast("Unknown command from server");
}

void Engine::sbp(StringVector values)
{
    return;
}
