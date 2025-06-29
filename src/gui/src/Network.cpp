/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#include "../includes/Network.hpp"
    
Zappy::Network::Network(Zappy::GUI *gui)
{
    if (!gui)
        throw Error("Gui not provided", "Network init");
    this->_gui = gui;
    this->_mapSize = {-1, -1};
    this->_playerNb = -1;
}

Zappy::Network::~Network()
{
    this->_socket.disconnect();
}

void Zappy::Network::send(std::string message)
{
    sf::Socket::Status status = this->_socket.send(message.c_str(), message.size());
    if (status == sf::Socket::Partial)
        status = this->_socket.send(message.c_str(), message.size());
    if (status != sf::Socket::Done)
        throw Error("Error", "Network Send function");
}

std::string Zappy::Network::receive(bool isBlocking)
{
    std::array<char, 4096> recievedArray;
    size_t nb_bytes;
    this->_socket.setBlocking(isBlocking);
    if (_socket.receive(recievedArray.data(), recievedArray.size(), nb_bytes) == sf::Socket::Done) {
        recievedArray[nb_bytes] = '\0';
        return std::string(recievedArray.data());
    }
    return "";
}

void Zappy::Network::establishConnection(std::string ip, size_t socket)
{
    sf::IpAddress ipAddress(ip);
    this->_status = _socket.connect(ipAddress, socket);
    if (this->_status != sf::Socket::Done)
        throw Error("Error", "Network Init function");
    std::string message = this->receive();
    if (this->_gui->isDebugging())
        std::cout << "[DEBUG] WELCOME MESSAGE FROM SERVER:" << message << std::endl;
}

void Zappy::Network::initProcess()
{
    this->askToServer("Team", {});
    this->askToServer("PlayerNb", {});
    this->askToServer("EggNb", {});
    this->askToServer("MapSize", {});
    this->_gui->initMap(this->_mapSize.x, this->_mapSize.y);
    this->askToServer("MapContent", {});
    this->askToServer("PlayersInfo", {});
    this->askToServer("EggsInfo", {});
}

void Zappy::Network::recieveFromServer()
{
    Parser parser;
    sf::Clock clock;
    while (!this->_isShuttingDown) {
        try {
            if (clock.getElapsedTime().asSeconds() > 10) {
                clock.restart();
                this->send("mct\n");
            }
            std::string recievedString = this->receive(false);
            if (!recievedString.empty()) {
                std::vector<std::string> tab = Parser::splitLine(recievedString, "\n");
                for (size_t i = 0; i < tab.size(); i++) {
                    std::vector<std::string> args = Parser::parseLine(tab[i], ' ');
                    parser.manageResponse(args, this);
                }
            }
        } catch(const Error& e) {
            this->_isShuttingDown = true;
            this->getGui()->quitGameToMenu();
        }
    }
    this->_socket.disconnect();
}

void Zappy::Network::askToServer(const std::string& command, std::vector<int> args)
{
    std::map<std::string, void (Network:: *)()> funcTabNoArgs = {
        {"Team", &Network::askTeam},
        {"PlayerNb", &Network::askPlayerNb},
        {"EggNb", &Network::askEggNb},
        {"PlayersInfo", &Network::askPlayersInfo},
        {"MapSize", &Network::askMapSize},
        {"MapContent", &Network::askMapContent},
        {"TimeUnitRequest", &Network::askTimeUnitRequest},
        {"EggsInfo", &Network::askEggsInfo},
    };
    std::map<std::string, void (Network:: *)(std::vector<std::string>)> funcTabWithArgs = {
        {"TileContent", &Network::askTileContent},
        {"PlayerPos", &Network::askPlayerPos},
        {"PlayerLevel", &Network::askPlayerLevel},
        {"PlayerInventory", &Network::askPlayerInventory},
        {"TimeUnitModif", &Network::askTimeUnitModif},
    };

    if (args.empty() && funcTabNoArgs[command])
        return (this->*funcTabNoArgs[command])();
    if (!args.empty() && funcTabWithArgs[command])
        return (this->*funcTabWithArgs[command])(Parser::argsToString(args));
}

void Zappy::Network::askTeam()
{
    this->send("GRAPHIC\n");
    [[maybe_unused]] std::string recievedString = this->receive();
    if (recievedString == "Maximum number of GUI clients reached.\n")
        throw Error("Server slot full", "Network Init function");
    if (this->_gui->isDebugging())
        std::cout << "[DEBUG from GUI] Authentification sucess" << std::endl;
}

void Zappy::Network::askPlayerNb()
{
    this->send("pnu\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(args, this);
}

void Zappy::Network::askEggNb()
{
    this->send("enu\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(args, this);
}

void Zappy::Network::askPlayersInfo()
{
    if (this->_playerNb <= 0) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Must have player number set before asking for players info." << std::endl;
        return;
    }
    this->send("pls\n");
    Parser parser;
    std::string playersInfo = "";
    while (true) {
        std::string recievedString = this->receive(false);
        playersInfo.append(recievedString);
        if (static_cast<int>(Parser::nbOccur(playersInfo, "pls")) >= this->_playerNb)
            break;
    }
    std::vector<std::string> tab = Parser::splitLine(playersInfo, "\n");
    for (size_t i = 0; i < tab.size(); i++) {
        std::vector<std::string> args = Parser::parseLine(tab[i], ' ');
        parser.manageResponse(args, this);
    }
}

void Zappy::Network::askEggsInfo()
{
    if (this->_eggNb <= 0) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Must have player number set before asking for players info." << std::endl;
        return;
    }
    this->send("els\n");
    Parser parser;
    std::string eggsInfo = "";
    while (true) {
        std::string recievedString = this->receive(false);
        eggsInfo.append(recievedString);
        if (static_cast<int>(Parser::nbOccur(eggsInfo, "els")) >= this->_eggNb)
            break;
    }
    std::vector<std::string> tab = Parser::splitLine(eggsInfo, "\n");
    for (size_t i = 0; i < tab.size(); i++) {
        std::vector<std::string> args = Parser::parseLine(tab[i], ' ');
        parser.manageResponse(args, this);
    }
}

void Zappy::Network::askMapSize()
{
    this->send("msz\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(args, this);
}

void Zappy::Network::askMapContent()
{
    if (this->_mapSize.x <= 0 || this->_mapSize.y <= 0) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Must have map size set before asking for content." << std::endl;
        return;
    }
    this->send("mct\n");
    Parser parser;
    std::string mapContent = "";
    while (true) {
        std::string recievedString = this->receive(false);
        mapContent.append(recievedString);
        if (static_cast<int>(Parser::nbOccur(mapContent, "bct")) >= this->_mapSize.x * this->_mapSize.y)
            break;
    }
    std::vector<std::string> tab = Parser::splitLine(mapContent, "\n");
    for (size_t i = 0; i < tab.size(); i++) {
        std::vector<std::string> args = Parser::parseLine(tab[i], ' ');
        parser.manageResponse(args, this);
    }
}

void Zappy::Network::askTimeUnitRequest()
{
    this->send("sgt\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(args, this);
}

void Zappy::Network::askTileContent([[maybe_unused]] std::vector<std::string> args)
{
    if (args.size() != 2) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Wrong number of arguments" << std::endl;
        return;
    }
    if (!Parser::isNum(args[0]) || !Parser::isNum(args[1])) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers" << std::endl;
        return;
    }
    this->send("bct " + args[0] + " " + args[1] + "\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> responseArgs = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(responseArgs, this);
}

void Zappy::Network::askPlayerPos([[maybe_unused]] std::vector<std::string> args)
{
    if (args.size() != 1) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Wrong number of arguments" << std::endl;
        return;
    }
    if (!Parser::isNum(args[0])) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers" << std::endl;
        return;
    }
    this->send("ppo #" + args[0] + "\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> responseArgs = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(responseArgs, this);
}

void Zappy::Network::askPlayerLevel([[maybe_unused]] std::vector<std::string> args)
{
    if (args.size() != 1) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Wrong number of arguments" << std::endl;
        return;
    }
    if (!Parser::isNum(args[0])) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers" << std::endl;
        return;
    }
    this->send("plv #" + args[0] + "\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> responseArgs = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(responseArgs, this);
}

void Zappy::Network::askPlayerInventory([[maybe_unused]] std::vector<std::string> args)
{
    if (args.size() != 1) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Wrong number of arguments" << std::endl;
        return;
    }
    if (!Parser::isNum(args[0])) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers" << std::endl;
        return;
    }
    this->send("pin #" + args[0] + "\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> responseArgs = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(responseArgs, this);
}

void Zappy::Network::askTimeUnitModif([[maybe_unused]] std::vector<std::string> args)
{
    if (args.size() != 1) {
        if (this->_gui->isDebugging())
            std::cout << "[DEBUG] Wrong number of arguments" << std::endl;
        return;
    }
    if (!Parser::isNum(args[0])) {
        if (this->_gui->isDebugging())
            std::cout << "DEBUGArgs must be positive numbers" << std::endl;
        return;
    }
    this->send("sst " + args[0] + "\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> responseArgs = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(responseArgs, this);
}
