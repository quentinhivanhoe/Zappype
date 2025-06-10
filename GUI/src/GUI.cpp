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
        this->_window.display();
    }   
}
