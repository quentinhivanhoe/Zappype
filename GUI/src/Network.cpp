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

std::string Zappy::Network::receive()
{
    std::array<char, 4096> recievedArray;
    size_t nb_bytes;
    if (_socket.receive(recievedArray.data(), recievedArray.size(), nb_bytes) == sf::Socket::Done) {
        recievedArray[nb_bytes] = '\0';
        return std::string(recievedArray.data());
    }
    throw Error("Error", "Network Recieve function");
    return "error";
}

void Zappy::Network::establishConnection(std::string ip, size_t socket)
{
    sf::IpAddress ipAddress(ip);
    this->_status = _socket.connect(ipAddress, socket);
    if (this->_status != sf::Socket::Done)
        throw Error("Error", "Network Init function");
    std::cout << "WELCOME MESSAGE FROM SERVER:" << this->receive() << std::endl;
}

void Zappy::Network::initProcess()
{
    this->askToServer("Team");
    this->askToServer("PlayerNb");
    this->askToServer("MapSize");
    this->askToServer("PlayersInfo");
    this->askToServer("MapContent");
    std::cout << "Initialisation process sucess" << std::endl;
}

void Zappy::Network::askToServer(const std::string& command)
{
    std::map<std::string, void (Network:: *)()> funcTab = {
        {"Team", &Network::askTeam},
        {"PlayerNb", &Network::askPlayerNb},
        {"PlayersInfo", &Network::askPlayersInfo},
        {"MapSize", &Network::askMapSize},
        {"MapContent", &Network::askMapContent},
    };
    if (funcTab[command])
        (this->*funcTab[command])();
    else
        std::cout << "command not found." << std::endl;
}

void Zappy::Network::askTeam()
{
    this->send("GRAPHIC\n");
}

void Zappy::Network::askPlayerNb()
{
    this->send("spn\n");
    std::string recievedString = this->receive();
    Parser parser;
    std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
    parser.manageResponse(args, this);
}

void Zappy::Network::askPlayersInfo()
{
    if (this->_playerNb < 0) {
        std::cout << "Must have player number set before asking for players info." << std::endl;
        return;
    }
    this->send("spi\n");
    Parser parser;
    for (int i = 0; i < this->_playerNb; i++) {
        std::string recievedString = this->receive();
        std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
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
        std::cout << "Must have map size set before asking for content." << std::endl;
        return;
    }
    this->send("mct\n");
    Parser parser;
    for (int i = 0; i < this->_mapSize.x * this->_mapSize.y; i++) {
        std::string recievedString = this->receive();
        std::vector<std::string> args = Parser::parseLine(recievedString, ' ');
        parser.manageResponse(args, this);
    }
}
