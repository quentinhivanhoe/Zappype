/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Egg functions
*/

#include "../includes/Egg.hpp"

Zappy::Egg::Egg(size_t id, sf::Vector2i indexPos, const std::string& teamName)
{
    this->_id = id;
    this->_indexPos = indexPos;
    this->_teamName = teamName;
    this->_drawable = std::make_shared<Drawable>("assets/egg_filled.png", 0.075 * 12.34);
    this->_drawable->getSprite().setOrigin(sf::Vector2f(this->_drawable->getTexture().getSize().x / 2.0, this->_drawable->getTexture().getSize().y / 2.0));
}
