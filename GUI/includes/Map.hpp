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
    #include "Tile.hpp"
    #include "Team.hpp"

namespace Zappy
{
    class Map
    {
    private:
        std::vector<Team> _teams;
        std::vector<std::vector<std::shared_ptr<Tile>>> _tiles;
        Vector2D _size;
    public:
        Map(Vector2D size = Vector2D(5.0, 5.0));
        ~Map();
        void init();
        Vector2D getSize() const {return this->_size;};
        std::vector<Team> getTeams() const {return this->_teams;};
        std::vector<std::vector<std::shared_ptr<Tile>>> getTiles() {return this->_tiles;};
    };
}

#endif /* !MAP_HPP_ */
