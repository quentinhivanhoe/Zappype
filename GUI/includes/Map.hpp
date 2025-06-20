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
    class Team;
    class Trantorian;
    class TrantorButtons;
    class GUI;
    class Tile;
    class Map
    {
    private:
        std::map<std::string, std::shared_ptr<Team>> _teams;
        std::map<size_t, std::shared_ptr<Trantorian>> _trantorians;
        std::vector<std::vector<std::shared_ptr<Tile>>> _tiles;
        Vector2D _size;
    public:
        Map(Vector2D size = Vector2D(5.0, 5.0));
        ~Map();
        void init();
        inline Vector2D getSize() const {return this->_size;};
        inline std::map<std::string, std::shared_ptr<Team>> getTeams() const { return this->_teams; };
        inline std::vector<std::vector<std::shared_ptr<Tile>>> getTiles() {return this->_tiles;};
        inline std::shared_ptr<Trantorian> getTrantorianByID(size_t id) { return this->_trantorians[id]; };
        inline std::map<size_t, std::shared_ptr<Trantorian>> getAllTrantorians() const { return this->_trantorians; };
        void addTrantorian(std::shared_ptr<Trantorian> trantorian);
    };
}

#endif /* !MAP_HPP_ */
