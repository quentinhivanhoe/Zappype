/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include <memory>
    #include <array>
    #include <iostream>
    #include "Error.hpp"
    #include "Parser.hpp"
    #include "SFML/Network.hpp"
    #include "GUI.hpp"
namespace Zappy 
{
    class GUI;
    class Network
    {
        private:
            GUI *_gui;
            sf::TcpSocket _socket;
            sf::Socket::Status _status;
            sf::Packet _packet;
            int _playerNb;
            sf::Vector2i _mapSize;
        public:
            Network(GUI *gui = nullptr);
            ~Network();

            //Setters
            inline void setPlayerNb(int nb) { this->_playerNb = nb;};
            inline void setMapSize(sf::Vector2i mapSize) { this->_mapSize = mapSize;};

            //Getters
            inline int getPlayerNb() const { return this->_playerNb; };
            inline sf::Vector2i getMapSize() const { return this->_mapSize; };
            inline GUI *getGui() const { return this->_gui; };
            inline void updateGUi() {};
            void establishConnection(std::string ip, size_t socket);
            void initProcess();
            void send(std::string message);
            std::string receive(bool isBlocking = true);
            inline void fetchData() {};
            void askToServer(const std::string& command, std::vector<int> args);
            void askTeam();
            void askPlayerNb();
            void askPlayersInfo();
            void askMapSize();
            void askMapContent();
            void askTimeUnitRequest();
            void askTileContent(std::vector<std::string> args);
            void askPlayerPos(std::vector<std::string> args);
            void askPlayerLevel(std::vector<std::string> args);
            void askPlayerInventory(std::vector<std::string> args);
            void askTimeUnitModif(std::vector<std::string> args);
    };
}

#endif /* !NETWORK_HPP_ */
