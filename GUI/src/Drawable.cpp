/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Stones
*/

#include "../includes/Drawable.hpp"

Zappy::Drawable::Drawable(std::string texture_path)
{
    this->_texture = sf::Texture();
    this->_texture.loadFromFile(texture_path);
    this->_sprite = sf::Sprite(_texture);
}

Zappy::Drawable::~Drawable()
{
}
void Zappy::Drawable::setTexture(sf::Texture texture)
{
    this->_texture = texture;
}

void Zappy::Drawable::setSprite(sf::Sprite sprite)
{
    this->_sprite = sprite;
}