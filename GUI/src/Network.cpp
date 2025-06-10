/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#include "../includes/Network.hpp"
#include "iostream"

    
Zappy::Network::Network(/* args */)
{
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
    char array[4096];
    size_t nb_bytes;
    if (_socket.receive(array, sizeof(array), nb_bytes) == sf::Socket::Done) {
        std::cout << array << std::endl;
        return std::string(array);
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
    std::cout << "FROM SERVER:" << this->receive() << std::endl;
}

void Zappy::Network::initProcess()
{
    this->askToServer("Team");
    this->askToServer("PlayerNb");
    this->askToServer("PlayersInfo");
    this->askToServer("MapSize");
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
    std::cout << "Asking for teams..." << std::endl;
}

void Zappy::Network::askPlayerNb()
{
    std::cout << "Asking for players number..." << std::endl;
}

void Zappy::Network::askPlayersInfo()
{
    std::cout << "Asking for players info..." << std::endl;
}

void Zappy::Network::askMapSize()
{
    std::cout << "Asking for map size..." << std::endl;
}

void Zappy::Network::askMapContent()
{
    std::cout << "Asking for map content..." << std::endl;
}
