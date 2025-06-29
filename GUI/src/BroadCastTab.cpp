/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** BroadCastTab functions
*/

#include "../includes/BroadCastTab.hpp"

Zappy::BroadCastTab::BroadCastTab()
{
    this->_bg.setSize(sf::Vector2f(600, 200));
    this->_bg.setFillColor(sf::Color(255, 255, 255, 150));
    this->_bg.setOutlineColor(sf::Color(150, 150, 150));
    this->_bg.setOutlineThickness(2);
    this->_bg.setOrigin(300, 100);
    this->_bg.setPosition(1920 - (this->_bg.getSize().x / 2) - 30, 1080 - (this->_bg.getSize().y / 2) - 30);
    this->_font.loadFromFile("assets/arial.ttf");
    this->_text.setFont(this->_font);
}

void Zappy::BroadCastTab::drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window)
{
    this->_text.setString(string);
    this->_text.setPosition(position);
    this->_text.setFillColor(color);
    this->_text.setCharacterSize(characterSize);
    window.draw(this->_text);
}

void Zappy::BroadCastTab::render(sf::RenderWindow &window)
{
    sf::Vector2f bgPos = this->_bg.getPosition();
    sf::Vector2f bgSize = this->_bg.getSize();
    if (!this->_messages.size())
        return;
    window.draw(this->_bg);
    for (size_t i = 0; i < this->_messages.size(); i++) {
        this->drawText(this->_messages[i], sf::Vector2f(bgPos.x - bgSize.x / 2 + 20, bgPos.y + bgSize.y / 2 - 45 - (50 * i)), sf::Color::Black, 30, window);
    }
}

void Zappy::BroadCastTab::update()
{
    
    this->_bg.setSize(sf::Vector2f(this->_bg.getSize().x, this->_messages.size() * 50));
    this->_bg.setOrigin(sf::Vector2f(this->_bg.getSize().x / 2.0, this->_bg.getSize().y / 2.0));
    this->_bg.setPosition(1920 - (this->_bg.getSize().x / 2) - 30, 1080 - (this->_bg.getSize().y / 2) - 100);
    if (this->_clock.getElapsedTime().asMilliseconds() < 3000 || !this->_messages.size())
        return;
    this->_clock.restart();
    this->_messages.pop_back();
}

void Zappy::BroadCastTab::pushToMessages(const std::string& messages)
{
    while (this->_messages.size() >= this->_maxMessagesSize)
        this->_messages.pop_back();
    this->_messages.insert(this->_messages.begin(), messages);
}
