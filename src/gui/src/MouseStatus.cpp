/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** mouse status function
*/

#include "../includes/MouseStatus.hpp"

Zappy::MouseStatus::MouseStatus(bool isForUI) : _pressed(false), _hold(false), _released(false)
{
    this->_hitbox.setFillColor(sf::Color::White);
    this->_hitbox.setSize({10, 10});
    this->_hitbox.setOrigin({5, 5});
    this->_hitbox.setOutlineColor(sf::Color::Red);
    this->_hitbox.setOutlineThickness(1);
    this->_isForUi = isForUI;
}

void Zappy::MouseStatus::update(sf::RenderWindow &window)
{
    sf::Vector2i mpos = sf::Mouse::getPosition(window);
    if (!this->_isForUi) {
        sf::View targetView = window.getView();
        sf::Vector2f scale(targetView.getSize().x / 1920.0, targetView.getSize().y / 1080.0);
        mpos.x *= scale.x;
        mpos.y *= scale.y;
        mpos.x += targetView.getCenter().x - (960 * scale.x);
        mpos.y += targetView.getCenter().y - (540 * scale.y);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->_hold)
            this->_pressed = true;
        else
            this->_pressed = false;
        this->_hold = true;
        this->_released = false;
    } else {
        if (this->_hold)
            this->_released = true;
        else
            this->_released = false;
        this->_hold = false;
        this->_pressed = false;
    }
    this->_hitbox.setPosition({(float)mpos.x, (float)mpos.y});
}

bool Zappy::MouseStatus::hover(sf::RectangleShape other)
{
    sf::FloatRect mouseHitBox = this->_hitbox.getGlobalBounds();
    sf::FloatRect otherHitBox = other.getGlobalBounds();

    if (mouseHitBox.intersects(otherHitBox)) {
        return true;
    }
    return false;
}
