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
    this->tile.getSprite().setScale(this->getTileScale(), this->getTileScale());
    this->_map = Map(Vector2D(7.0, 4.0));
    this->sky.getSprite().setPosition(0, 0);
    this->run();
}
    
Zappy::GUI::~GUI()
{
}

void Zappy::GUI::init()
{
    initPaths();
    for (int i = 0; i != 8; i++) {
        this->_items.push_back(std::make_shared<Items>(this->spritePaths[i], i));
    }
}

void Zappy::GUI::initPaths()
{
    this->spritePaths.push_back("../assets/egg_filed.png");
    this->spritePaths.push_back("../assets/food_filed.png");
    this->spritePaths.push_back("../assets/cristal_filed.png");
    this->spritePaths.push_back("../assets/cristal_filed.png");
    this->spritePaths.push_back("../assets/cristal_filed.png");
    this->spritePaths.push_back("../assets/cristal_filed.png");
    this->spritePaths.push_back("../assets/cristal_filed.png");
    this->spritePaths.push_back("../assets/cristal_filed.png");
}

void Zappy::GUI::handleWindowEvents(  )
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
            offset.setX(offset.getX() - tile.getTexture().getSize().x  * this->getTileScale() / (2));
            offset.setY(offset.getY() + tile.getTexture().getSize().y  * this->getTileScale() / (2) - 18);
            this->tile.getSprite().setPosition(offset.getX(), offset.getY());
            this->_window.draw(this->tile.getSprite());
        }
        offset = Vector2D(
        (1920/2 + (tile.getTexture().getSize().x * this->getTileScale() / 2) * j),
        (0 + (tile.getTexture().getSize().y * this->getTileScale() / 2 - 18) * j));
    }
}

void Zappy::GUI::display_sky()
{
    this->_window.draw(this->sky.getSprite());
}

void Zappy::GUI::display_objects()
{

}