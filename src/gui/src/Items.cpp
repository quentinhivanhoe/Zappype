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
    this->_sprite = std::make_shared<Drawable>(fileName, 0.075 * 12.34);
    this->_sprite->getSprite().setOrigin(sf::Vector2f(this->_sprite->getTexture().getSize().x / 2.0, this->_sprite->getTexture().getSize().y / 2.0));
}
    
Zappy::Items::~Items()
{
}