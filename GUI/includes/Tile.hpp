/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_
    #include "iostream"
    #include "vector"
    #include "Math/Vector2D.hpp"
namespace Zappy
{
    enum Item {
        EGG = 0,
        FOOD = 1,
        LINEMATE = 2,
        DERAUMERE = 3,
        SIBUR = 4,
        MENDIANE = 5,
        PHIRAS = 6,
        THYSTAME = 7,
    };
    class Tile
    {
    private:
        size_t _id;
        std::vector<size_t> _items;
        Vector2D _pos;
    public:
        Tile(size_t id = -1);
        ~Tile();
        size_t getId() const {return this->_id;};
        size_t getNItem(Item name);
        void setNItem(Item name, size_t value);
        Vector2D getPos() const {return this->_pos;};
        void setPos(Vector2D pos) {this->_pos = pos;};
    }; 
}

#endif /* !TILE_HPP_ */
