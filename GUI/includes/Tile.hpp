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
    public:
        Tile(size_t id = -1);
        ~Tile();
        size_t getNItem(Item name);
        void setNItem(Item name, size_t value);
    }; 
}

#endif /* !TILE_HPP_ */
