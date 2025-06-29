/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Tile
*/

#include "../includes/Tile.hpp"

Zappy::Tile::Tile(size_t id)
{
    this->_id = id;
    for (int i = 0; i != 8; i++) {
        this->_items.push_back(2);
    }
}

void Zappy::Tile::initButton(Zappy::GUI *gui, std::shared_ptr<Tile> tile)
{
    this->_innerButton = std::make_shared<TileButtons>(gui, tile);
    this->_innerButton->setPosition(sf::Vector2f(this->_pos.getX() + 195, this->_pos.getY() + 180));
    this->_innerButton->setBgFillColor(sf::Color(255, 255, 255, 100));
    this->_innerButton->setSize({200, 110});
    this->_innerButton->setMaxScale({1, 1});
    this->_innerButton->setMinScale({1, 1});
}

Zappy::Tile::~Tile()
{

}

size_t Zappy::Tile::getNItem(Zappy::Item name)
{
    return (this->_items[name]);
}

void Zappy::Tile::setNItem(Zappy::Item name, size_t value)
{
    this->_items[name] = value;
}

void Zappy::Tile::setOffsetsList(std::vector<Vector2D> offsets)
{
    this->offsets_list = offsets;
}