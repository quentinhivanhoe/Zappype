/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_
    #include <memory>
    #include "Interfaces/IObject.hpp"
    #include "Team.hpp"

namespace Zappy
{
    class Map
    {
    private:
        std::vector<Team> _teams;
        std::vector<std::shared_ptr<IObject>> _stones;
        std::vector<std::shared_ptr<IObject>> _foods;
    public:
        Map();
        ~Map();
        void init();
        std::vector<Team> getTeams() const {return this->_teams;};
        std::vector<std::shared_ptr<IObject>> getStones() const {return this->_stones;};
        std::vector<std::shared_ptr<IObject>> getFoods() const {return this->_foods;};
    };
    
   
    
}

#endif /* !MAP_HPP_ */
