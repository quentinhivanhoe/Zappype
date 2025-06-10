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
    this->_packet << message;
    if (this->_socket.send(_packet) != sf::Socket::Done)
        std::cout << "send error" << std::endl;
}

std::string Zappy::Network::receive()
{
    if (_socket.receive(_packet) == sf::Socket::Done) {
        std::string message;
        _packet >> message;
        return message;
    }
    return "error";
}

void Zappy::Network::init(std::string ip, size_t socket)
{
    this->_socket.setBlocking(false);
    this->_status = _socket.connect(ip, socket);
    if (this->_status != sf::Socket::Done)
        std::cout << "error connection" << std::endl;
    this->send("GRAPHIC");
}