/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include <memory>
    #include "SFML/Network.hpp"
namespace Zappy 
{
    class GUI;
    class Network
    {
        private:
            std::shared_ptr<GUI> _gui;
            sf::TcpSocket _socket;
            sf::Socket::Status _status;
            sf::Packet _packet;
        public:
            Network(/* args */);
            ~Network();
            inline void updateGUi() {};
            void init(std::string ip, size_t socket);
            void send(std::string message); //tmp param
            std::string receive(); //tmp param
            inline void fetchData() {};
    };
}

#endif /* !NETWORK_HPP_ */
