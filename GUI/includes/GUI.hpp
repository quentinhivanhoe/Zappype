/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** GUI
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include <memory>
    #include "Network.hpp"
    #include "Buttons.hpp"
    #include "Map.hpp"

namespace Zappy
{
    class Network;
    class GUI
    {
        private:

            std::vector<std::shared_ptr<Buttons>> _buttons;
            std::shared_ptr<Network> _networkInfo;
            sf::RenderWindow _window;
            Map _map;
            sf::Event _event;
        public:
            GUI(const std::string& ip = "127.0.0.1", size_t port = 8000);
            ~GUI();
            void init();
            void run();
            void handleWindowEvents();
            std::vector<std::shared_ptr<Buttons>> getButtons() const {return this->_buttons;};
            Map getMap() const {return this->_map;};
            std::shared_ptr<Network> getNetwork() const {return this->_networkInfo;};
    };
}

#endif /* !GUI_HPP_ */
//