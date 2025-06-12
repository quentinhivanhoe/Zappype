/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Items
*/

#include "../includes/Items.hpp"

Zappy::Items::Items(const char *fileName, size_t id)
{
    this->_id = id;
    this->_sprite = Drawable(fileName);
}
    
Zappy::Items::~Items()
{
}