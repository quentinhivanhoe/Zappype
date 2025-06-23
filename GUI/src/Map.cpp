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

    this->init();
}
    
Zappy::Map::~Map()
{
}

void Zappy::Map::init() 
{
    size_t id_tmp = 0;
    for (int i = 0; i != this->_size.getY(); i++) {
        std::cout << "i" << i << std::endl;
        std::vector<std::shared_ptr<Tile>> tmp;
        for (int j = 0; j != this->_size.getX(); j++) {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(id_tmp);
            tile->setIndex(sf::Vector2i(j, i));
            tmp.push_back(tile);
            id_tmp++;
        }
        this->_tiles.push_back(tmp);
    }
}

void Zappy::Map::addTrantorian(std::shared_ptr<Zappy::Trantorian> trantorian)
{
    this->_trantorians[trantorian->getID()] = trantorian;
    if (!_teams[trantorian->getTeamName()])
        this->_teams[trantorian->getTeamName()] = std::make_shared<Team>(trantorian->getTeamName());
    this->_teams[trantorian->getTeamName()]->addTrantorian(trantorian);
}
