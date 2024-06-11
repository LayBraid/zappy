#include "Client/Client.hpp"
#include "Engine.hpp"
#include "Launcher.hpp"

int main(int ac, char **av)
{
    auto address = std::make_shared<std::string>("127.0.0.1");
    auto port = std::make_shared<std::string>("4242");

    if (Launcher launcher(ac, av); !launcher.display(address, port))
        return 1;
    Client client(*address, std::stoul(*port));
    if (!client.isConnected())
        return 1;
    Engine engine(client);
    engine.run();
}
