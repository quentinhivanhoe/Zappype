/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** GUI
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include "Player.hpp"
    #include "Buttons.hpp"
    #include "Interfaces/IObject.hpp"
    #include "Network.hpp"
namespace Zappy
{
    class Network;
    class GUI
    {
    private:
        std::vector<Player> _teams;
        std::vector<Buttons> _buttons;
        std::vector<IObject> _stones;
        std::vector<IObject> _foods;
        Network networkInfo;
    public:
        GUI(/* args */);
        ~GUI();
        void init();
        void run();
        std::vector<Player> getTeams() const {return this->_teams;};
        std::vector<Buttons> getButtons() const {return this->_buttons;};
        std::vector<IObject> getStones() const {return this->_stones;};
        std::vector<IObject> getFoods() const {return this->_foods;};

    };
}

#endif /* !GUI_HPP_ */
