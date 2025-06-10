/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include <memory>
    #include "Error.hpp"
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
            Network();
            ~Network();
            inline void updateGUi() {};
            void establishConnection(std::string ip, size_t socket);
            void initProcess();
            void send(std::string message); //tmp param
            std::string receive(); //tmp param
            inline void fetchData() {};
            void askToServer(const std::string& command);
            void askTeam();
            void askPlayerNb();
            void askPlayersInfo();
            void askMapSize();
            void askMapContent();
    };
}

#endif /* !NETWORK_HPP_ */
