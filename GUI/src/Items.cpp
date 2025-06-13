/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Items
*/

#include "../includes/Items.hpp"

Zappy::Items::Items(std::string fileName, size_t id)
{
    this->_id = id;
    std::cout << "Creating Item with :\"" << fileName << "\"" << std::endl;
    this->_sprite = std::make_shared<Drawable>(fileName);
}
    
Zappy::Items::~Items()
{
}