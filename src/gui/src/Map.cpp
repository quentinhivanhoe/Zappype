/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Map
*/

#include "../includes/Map.hpp"

Zappy::Map::Map(GUI *gui, Vector2D size)
{
    this->_gui = gui;
    _size = size;
    this->init();
}
    
Zappy::Map::~Map()
{
}

void Zappy::Map::init() 
{
    size_t id_tmp = 0;
    Vector2D offset = Vector2D(1920/2, 0);
    Vector2D size = Vector2D(500, 500);
    for (int i = 0; i != this->_size.getY(); i++) {
        std::vector<std::shared_ptr<Tile>> tmp;
        for (int j = 0; j != this->_size.getX(); j++) {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(id_tmp);
            tile->setIndex(sf::Vector2i(j, i));
            tile->getTile()->set_offsets();
            tile->setOffsetsList(tile->getTile()->get_offsets());
            Vector2D size = Vector2D(tile->getTile()->getTexture().getSize().x * this->_tileScale / (2) - 5, tile->getTile()->getTexture().getSize().y  * this->_tileScale / (2) - 85);
            offset.setX(offset.getX() - size.getX());
            offset.setY(offset.getY() + size.getY());
            tile->getTile()->getSprite().setPosition(offset.getX(), offset.getY());
            tile.get()->setCenter(Vector2D(offset.getX() + (size.getX()), offset.getY() + (size.getY())));
            tile.get()->setPos(offset);
            tile->initButton(this->_gui, tile);
            tmp.push_back(tile);
            id_tmp++;
        }
        this->_tiles.push_back(tmp);
        offset = Vector2D(
        (1920/2 + (size.getX() - 310) * (i + 1)),
        (0 + (size.getY() - 390) * (i + 1)));
    }
}

void Zappy::Map::addTrantorian(std::shared_ptr<Zappy::Trantorian> trantorian)
{
    this->_trantorians[trantorian->getID()] = trantorian;
    if (!_teams[trantorian->getTeamName()])
        this->_teams[trantorian->getTeamName()] = std::make_shared<Team>(trantorian->getTeamName());
    this->_teams[trantorian->getTeamName()]->addTrantorian(trantorian);
}

void Zappy::Map::addEgg(std::shared_ptr<Egg> egg)
{
    this->_eggs[egg->getId()] = egg;
    if (!_teams[egg->getTeamName()])
        this->_teams[egg->getTeamName()] = std::make_shared<Team>(egg->getTeamName());
    this->_teams[egg->getTeamName()]->addEgg(egg);
}
