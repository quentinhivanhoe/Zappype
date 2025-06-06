/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** GUI
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include "Buttons.hpp"
    #include "Network.hpp"
    #include "Map.hpp"

namespace Zappy
{
    class Network;
    class GUI
    {
    private:
        
        std::vector<Buttons> _buttons;
        Network _networkInfo;
        sf::RenderWindow _window;
        Map _map;
    public:
        GUI();
        ~GUI();
        void init();
        void run();
        std::vector<Buttons> getButtons() const {return this->_buttons;};
        Map getMap() const {return this->_map;};
        Network getNetwork() const {return this->_networkInfo;};
    };
}

#endif /* !GUI_HPP_ */
