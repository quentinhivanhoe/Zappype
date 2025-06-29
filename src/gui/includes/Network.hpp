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
            int _eggNb;
            sf::Vector2i _mapSize;
            bool _isShuttingDown = false;
        public:
            Network(GUI *gui = nullptr);
            ~Network();

            //Setters

            /**
             * @brief Set the Player Nb object
             * 
             * @param nb 
             */
            inline void setPlayerNb(int nb) { this->_playerNb = nb;};

            /**
             * @brief Set the Egg Nb object
             * 
             * @param nb 
             */
            inline void setEggNb(int nb) { this->_eggNb = nb;};

            /**
             * @brief Set the Map Size object
             * 
             * @param mapSize 
             */
            inline void setMapSize(sf::Vector2i mapSize) { this->_mapSize = mapSize;};

            /**
             * @brief Recieve function for thread
             * 
             */
            void recieveFromServer();
            //Getters

            /**
             * @brief Get the Player Nb object
             * 
             * @return int 
             */
            inline int getPlayerNb() const { return this->_playerNb; };

            /**
             * @brief Get the Egg Nb object
             * 
             * @return int 
             */
            inline int getEggNb() const { return this->_eggNb; };

            /**
             * @brief Get the Map Size object
             * 
             * @return sf::Vector2i 
             */
            inline sf::Vector2i getMapSize() const { return this->_mapSize; };

            /**
             * @brief Get the Gui object
             * 
             * @return GUI* 
             */
            inline GUI *getGui() const { return this->_gui; };

            /**
             * @brief 
             * 
             */
            inline void updateGUi() {};

            /**
             * @brief Create the connection with the given IP and PORT
             * 
             * @param ip 
             * @param socket 
             */
            void establishConnection(std::string ip, size_t socket);

            /**
             * @brief Init process to handle communication
             * 
             */
            void initProcess();

            /**
             * @brief Send function to the server
             * 
             * @param message 
             */
            void send(std::string message);

            /**
             * @brief Recieve function from the server
             * 
             * @param isBlocking 
             * @return std::string 
             */
            std::string receive(bool isBlocking = true);

            /**
             * @brief Deprecated
             * 
             */
            inline void fetchData() {};

            /**
             * @brief Global function to ask request to the server
             * 
             * @param command 
             * @param args 
             */
            void askToServer(const std::string& command, std::vector<int> args);

            /**
             * @brief Send GRAPHIC to server to initialise its teams
             * 
             */
            void askTeam();

            /**
             * @brief Send PNU to server to get the players number
             * 
             */
            void askPlayerNb();

            /**
             * @brief Send ENU to the server to get the eggs number
             * 
             */
            void askEggNb();

            /**
             * @brief Send PLS to the server to get the players list
             * 
             */
            void askPlayersInfo();

            /**
             * @brief Send MSZ to the server to get the map size
             * 
             */
            void askMapSize();

            /**
             * @brief Send MCT to the server to get the whole map content
             * 
             */
            void askMapContent();

            /**
             * @brief Send SST to the server to get the Time Unit
             * 
             */
            void askTimeUnitRequest();

            /**
             * @brief Send ELS to the server to get the egg list
             * 
             */
            void askEggsInfo();

            /**
             * @brief Send MCT to the server to get the content of a single tile
             * 
             * @param args 
             */
            void askTileContent(std::vector<std::string> args);

            /**
             * @brief Send PPO to the server to get the position and orientation of the given player
             * 
             * @param args 
             */
            void askPlayerPos(std::vector<std::string> args);

            /**
             * @brief Send PLV to the server to get the current level of the given player
             * 
             * @param args 
             */
            void askPlayerLevel(std::vector<std::string> args);

            /**
             * @brief Send PIN to the server to get the current inventory of the given player
             * 
             * @param args 
             */
            void askPlayerInventory(std::vector<std::string> args);

            /**
             * @brief Send SGT to the server to change the Time Unit of the server
             * 
             * @param args 
             */
            void askTimeUnitModif(std::vector<std::string> args);

            /**
             * @brief Shutdown the reciever thread
             * 
             */
            inline void shutDown() { this->_isShuttingDown = true; };
    };
}

#endif /* !NETWORK_HPP_ */
