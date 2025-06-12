/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** GUI
*/
#include "../includes/GUI.hpp"

Zappy::GUI::GUI(/* args */)
{
    this->_window.create(sf::VideoMode(1920, 1080, 8), "Zappy GUI", sf::Style::Close);

    this->tile_texture = sf::Texture();
    this->tile_texture.loadFromFile("../GUI/assets/map.png");

    this->tile = sf::Sprite(tile_texture);
    this->tile.setScale(this->getTileScale(), this->getTileScale());
    this->_map = Map(Vector2D(4.0, 4.0));

    this->sky_texture = sf::Texture();
    this->sky_texture.loadFromFile("../GUI/assets/sky.jpg");
    this->sky = sf::Sprite(sky_texture);
    this->sky.setPosition(0, 0);
    this->run();
}
    
Zappy::GUI::~GUI()
{
}

void Zappy::GUI::init()
{

}

void Zappy::GUI::handleWindowEvents()
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            this->_window.close();
    }   
}

void Zappy::GUI::run()
{
    while (this->_window.isOpen()) {
        this->handleWindowEvents();
        this->_window.clear(sf::Color::Black);
        this->display_sky();
        this->display_map();
        this->_window.display();
    }   
}

void Zappy::GUI::display_map()
{
    Vector2D offset = Vector2D(1920/2, 0);

    for (size_t j = 0; j < this->getMap().getSize().getY() + 1; j++){
        for (int i = 0; i < this->getMap().getSize().getX(); i++){
            offset.setX(offset.getX() - tile_texture.getSize().x  * this->getTileScale() / (2));
            offset.setY(offset.getY() + tile_texture.getSize().y  * this->getTileScale() / (2) - 18);
            this->tile.setPosition(offset.getX(), offset.getY());
            this->_window.draw(this->tile);
        }
        offset = Vector2D(
        (1920/2 + (tile_texture.getSize().x * this->getTileScale() / 2) * j),
        (0 + (tile_texture.getSize().y * this->getTileScale() / 2 - 18) * j));
    }
}

void Zappy::GUI::display_sky()
{
    this->_window.draw(this->sky);
}