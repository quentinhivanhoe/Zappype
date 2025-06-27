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
    this->_drawable = std::make_shared<Drawable>("../GUI/assets/egg_filled.png", 0.075);
}
