/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Stones
*/

#include "../includes/Drawable.hpp"
#include <random>
#include <chrono>
#include "Drawable.hpp"

Zappy::Drawable::Drawable(std::string texture_path, float scale)
{
    this->_texture.loadFromFile(texture_path);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setScale(scale, scale);
}

Zappy::Drawable::~Drawable()
{
}

void Zappy::Drawable::setTexture(sf::Texture texture)
{
    this->_texture = texture;
}

void Zappy::Drawable::updateTextureFromPath(std::string filepath)
{
    sf::Texture tmp;
    tmp.loadFromFile(filepath);
    this->setTexture(tmp);
}

void Zappy::Drawable::shuffler(std::vector<Vector2D> tab, unsigned seed)
{   
    (void)tab;
    (void)seed;
    return;   
}

void Zappy::Drawable::setSprite(sf::Sprite sprite)
{
    this->_sprite = sprite;
}

void Zappy::Drawable::set_offsets()
{
    this->offsets.clear();
    float half_x = this->getTexture().getSize().x * this->getSprite().getScale().x / 2;
    float half_y = this->getTexture().getSize().y * this->getSprite().getScale().y / 2;
    float quarter_x = half_x / 2;
    float quarter_y = half_y / 2;
    float half_quarter_x = quarter_x / 2;
    float half_quarter_y = quarter_y / 2;

    this->offsets.push_back(Vector2D(half_quarter_x + 10, half_quarter_y - 20));
    this->offsets.push_back(Vector2D(half_quarter_x + 10, -half_quarter_y));
    this->offsets.push_back(Vector2D(-half_quarter_x - 10, half_quarter_y - 20));
    this->offsets.push_back(Vector2D(-half_quarter_x - 10, -half_quarter_y));
    this->offsets.push_back(Vector2D(0, quarter_y - 40));
    this->offsets.push_back(Vector2D(0, -quarter_y + 0));
    this->offsets.push_back(Vector2D(-quarter_x - 10, -10));
    this->offsets.push_back(Vector2D(quarter_x + 10, -10));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->offsets.begin(), this->offsets.end(), std::default_random_engine(seed));
}
