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
    this->tile.setScale(0.25, 0.25);
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
        this->display_map();
        this->_window.display();
    }   
}

void Zappy::GUI::display_map()
{
    Vector2D offset = Vector2D(1920/2, 1080/2);

    for (size_t j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++){
            offset.setX(offset.getX() - 120);
            offset.setY(offset.getY() + 70);
            this->tile.setPosition(offset.getX(), offset.getY());
            this->_window.draw(this->tile);
        }
    }
    
}

