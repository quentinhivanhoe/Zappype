/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Trantorian
*/
#include "../includes/Trantor.hpp"

Zappy::Trantorian::Trantorian(/* args */)
{
    this->_inventory = std::make_shared<Tile>();
    this->_sprite = std::make_shared<Drawable>("../GUI/assets/untitled.png", 0.1);
    this->getSprite()->getSprite().setOrigin(this->getSprite()->getTexture().getSize().x / 2, this->getSprite()->getTexture().getSize().y / 2 + 400);
}
    
Zappy::Trantorian::~Trantorian()
{
}
   