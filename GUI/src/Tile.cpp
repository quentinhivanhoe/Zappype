/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Tile
*/

#include "../includes/Tile.hpp"
#include "Tile.hpp"

Zappy::Tile::Tile(size_t id)
{
    this->_id = id;
    for (int i = 0; i != 8; i++) {
        this->_items.push_back(1);
    }
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