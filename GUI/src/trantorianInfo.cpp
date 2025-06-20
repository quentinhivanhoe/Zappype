/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Trantorian info functions
*/

#include "../includes/TrantorianInfo.hpp"

Zappy::TrantorianInfo::TrantorianInfo(GUI *gui)
{
    if (!gui)
        throw Error("Missing GUI", "TrantorianInfo init");
    this->_gui = gui;
    this->_bg.setSize({320, 1010});
    this->_bg.setFillColor(sf::Color(240, 240, 240));
    this->_bg.setOutlineColor(sf::Color::Black);
    this->_bg.setOutlineThickness(1);
    this->_bg.setPosition({320, 60});
    this->_titleBarBg.setSize({320, 50});
    this->_titleBarBg.setFillColor(sf::Color::White);
    this->_titleBarBg.setOutlineColor(sf::Color::Black);
    this->_titleBarBg.setOutlineThickness(1);
    this->_titleBarBg.setPosition({320, 10});
}

void Zappy::TrantorianInfo::update(Zappy::MouseStatus mouse)
{
    if (!this->_trantorian)
        return;
    (void)mouse;
}

void Zappy::TrantorianInfo::render(sf::RenderWindow &window)
{
    if (!this->_trantorian)
        return;
    window.draw(this->_bg);
    window.draw(this->_titleBarBg);
}
