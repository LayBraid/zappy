#include "Launcher.hpp"

Launcher::Launcher(int ac, char *av[])
    : _window(sf::VideoMode(1080, 720), "Zappy Launcher"), _event(), _font(),
      _content(), _clock(),
      _address("Address", _font), _port("Port", _font),
      _colors{sf::Color::White, sf::Color::Red}
{
    _font.loadFromFile("gui/asset/ARIAL.TTF");

    _texture.loadFromFile("gui/asset/bgzappy.png");
    _background.setTexture(_texture);

    _address.setPosition(800, 300);
    _port.setPosition(800, 400);

    for (int i = 0; i < ac; i++) {
        auto arg = std::string(av[i]);
        if (arg == "-p" && i +1 < ac) defaultPort = av[i + 1];
        if (arg == "-h" && i +1 < ac) defaultAddress = std::string(av[i + 1]);
        if (arg == "-help") printHelpMessage();
    }
}

Launcher::~Launcher()
{
}

void Launcher::printHelpMessage()
{
    std::cout << "./zappy_gui -help" << std::endl;
    std::cout << "\tUSAGE: ./zappy_ai -p port -h machine" << std::endl;
    std::cout << "\tport is the port number" << std::endl;
    std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
    _validArgs = false;
}

bool Launcher::display(
std::shared_ptr<std::string> &address, std::shared_ptr<std::string> &port)
{
    if (!_validArgs)
        return false;
    if (defaultAddress.length() !=0)
        *address = defaultAddress;
    if (defaultPort.length() != 0)
        *port = defaultPort;
    if (defaultAddress.length() !=0 && defaultPort.length() !=0)
        return true;
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            switch (_event.type) {
            case sf::Event::Closed: _window.close(); break;

            case sf::Event::KeyPressed:
                if (_event.key.code == sf::Keyboard::Tab) {
                    _currentParam = (_currentParam + 1) % 2;
                    _colorIndex = 1;
                    _clock.restart();
                }
                if (_event.key.code == sf::Keyboard::Return ||
                _event.key.code == sf::Keyboard::Escape)
                    _window.close();
                if (_event.key.code == sf::Keyboard::Enter) {
                    _window.close();
                    unsigned long portValue = std::stoul(*port);
                    if (portValue == 0 || portValue > 65535)
                        return false;
                    return true;
                }
                break;

            case sf::Event::TextEntered:
                if (_currentParam == 0) {
                    if (_event.text.unicode == 8 && address->size() > 0)
                        address->pop_back();
                    else if (_event.text.unicode < 128 &&
                    _event.text.unicode > 10)
                        *address += static_cast<char>(_event.text.unicode);
                } else {
                    if (_event.text.unicode == 8 && port->size() > 0)
                        port->pop_back();
                    else if (_event.text.unicode >= 48 &&
                    _event.text.unicode <= 57 && port->size() < 5)
                        *port += static_cast<char>(_event.text.unicode);
                }
                break;

            default: break;
            }
        }

        if (_clock.getElapsedTime().asSeconds() > 0.6) {
            _colorIndex = (_colorIndex + 1) % 2;
            _clock.restart();
        }

        _window.clear();

        _window.setView(sf::View({0,0,1080,720}));
        _window.draw(_background);

        _address.setFillColor(_colors[_currentParam == 0 ? _colorIndex : 0]);
        _address.setString("Address: " + *address);
        _window.draw(_address);

        _port.setFillColor(_colors[_currentParam == 1 ? _colorIndex : 0]);
        _port.setString("Port: " + *port);
        _window.draw(_port);

        _window.display();
    }
    return false;
}
