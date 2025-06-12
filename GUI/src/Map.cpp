/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Map
*/

#include "../includes/Map.hpp"

Zappy::Map::Map(Vector2D size)
{
    _size = size;
}
    
Zappy::Map::~Map()
{
}

void Zappy::Map::init() 
{
    size_t id_tmp = 0;

    for (int i = 0; i != this->_size.getX(); i++) {
        std::vector<std::shared_ptr<Tile>> tmp;
        for (int j = 0; j != this->_size.getY(); j++) {
            tmp.push_back(std::make_shared<Tile>(id_tmp));
            id_tmp++;
        }
        this->_tiles.push_back(tmp);
    }
}