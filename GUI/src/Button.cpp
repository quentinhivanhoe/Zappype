/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** buttons functions
*/

#include "../includes/Buttons.hpp"
#include <iostream>

Zappy::Buttons::Buttons()
{
    this->_font.loadFromFile("assets/arial.ttf");
    this->_bg.setFillColor(sf::Color::White);
    this->_bg.setOutlineColor(sf::Color::Black);
    this->_bg.setOutlineThickness(1);
    this->_bg.setSize(this->_size);
    this->_bg.setPosition(this->_position);
    this->_bg.setOrigin({this->_position.x / 2, this->_position.y / 2});
    this->_title.setFont(this->_font);
    this->_title.setPosition(this->_position + this->_titlePositionOffset);
    this->_title.setString("default");
    this->_title.setCharacterSize(this->_characterSize);
    this->_title.setLetterSpacing(2);
    this->_title.setFillColor(sf::Color::Red);
    this->_title.setOutlineThickness(0.5);
}

Zappy::Buttons &Zappy::Buttons::setPosition(sf::Vector2f position)
{
    this->_position = position;
    this->_bg.setPosition(this->_position);
    this->_title.setPosition(this->_position + this->_titlePositionOffset);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setTitlePositionOffset(sf::Vector2f position)
{
    this->_titlePositionOffset = position;
    this->_title.setPosition(this->_position + this->_titlePositionOffset);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setSize(sf::Vector2f size)
{
    this->_size = size;
    this->_bg.setOrigin({this->_size.x / 2, this->_size.y / 2});
    this->_bg.setSize(size);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setRotation(float rotation)
{
    this->_rotation = rotation;
    this->_bg.setRotation(rotation);
    this->_title.setRotation(rotation);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setScale(sf::Vector2f scale)
{
    this->_scale = scale;
    this->_bg.setScale(scale);
    this->_title.setScale(scale);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setBaseScale(sf::Vector2f scale)
{
    this->_baseScale = scale;
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setMinScale(sf::Vector2f scale)
{
    this->_minScale = scale;
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setMaxScale(sf::Vector2f scale)
{
    this->_maxScale = scale;
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setCharacterSize(int size)
{
    this->_characterSize = size;
    this->_title.setCharacterSize(size);
    sf::Vector2f newSize = {this->_title.getGlobalBounds().width, this->_title.getGlobalBounds().height};
    this->_title.setOrigin({(float)(newSize.x / 2.0), (float)(newSize.y / 2.0)});
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setTitle(const std::string& title)
{
    this->_title.setString(title);
    sf::Vector2f newSize = {this->_title.getGlobalBounds().width, this->_title.getGlobalBounds().height};
    this->_title.setOrigin({(float)(newSize.x / 2.0), (float)(newSize.y / 2.0)});
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setBgOutlineColor(sf::Color color)
{
    this->_bg.setOutlineColor(color);
    this->_outlineColor = color;
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setBgFillColor(sf::Color color)
{
    this->_bg.setFillColor(color);
    this->_fillColor = color;
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setTextFillColor(sf::Color color)
{
    this->_title.setFillColor(color);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setTextOutlineColor(sf::Color color)
{
    this->_title.setOutlineColor(color);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::setFunction(std::function<void(void *)> function)
{
    this->_function = function;
    return *this;
}

Zappy::Buttons &Zappy::Buttons::rotateClockWise(float step)
{
    this->_bg.rotate(step);
    this->_title.rotate(step);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::rotateCounterClockWise(float step)
{
    this->_bg.rotate(-step);
    this->_title.rotate(-step);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::scaleUp(float step)
{
    float scaleX = this->_scale.x + step;
    float scaleY = this->_scale.y + step;

    Math::Clamp::function(&scaleX, this->_minScale.x, this->_maxScale.x);
    Math::Clamp::function(&scaleY, this->_minScale.y, this->_maxScale.y);
    this->setScale({scaleX, scaleY});
    return *this;
}

Zappy::Buttons &Zappy::Buttons::scaleDown(float step)
{
    float scaleX = this->_scale.x - step;
    float scaleY = this->_scale.y - step;

    Math::Clamp::function(&scaleX, this->_minScale.x, this->_maxScale.x);
    Math::Clamp::function(&scaleY, this->_minScale.y, this->_maxScale.y);
    this->setScale({scaleX, scaleY});
    return *this;
}

Zappy::Buttons &Zappy::Buttons::operator()(void *parameters)
{
    if (!this->_function)
        return *this;
    this->_function(parameters);
    return *this;
}

Zappy::Buttons &Zappy::Buttons::function(void *parameters)
{
    if (!this->_function)
        return *this;
    this->_function(parameters);
    return *this;
}

void Zappy::Buttons::render(sf::RenderWindow &window) const
{
    window.draw(this->_bg);
    window.draw(this->_title);
}

void Zappy::Buttons::update(MouseStatus mouse)
{
    float colorRed = this->_fillColor.r + 50 - 150 * mouse.hold();
    float colorGreen = this->_fillColor.g + 50 - 150 * mouse.hold();
    float colorBlue = this->_fillColor.b + 50 - 150 * mouse.hold();
    Math::Clamp::function(&colorRed, 0, 255);
    Math::Clamp::function(&colorGreen, 0, 255);
    Math::Clamp::function(&colorBlue, 0, 255);
    this->_bg.setFillColor(this->_fillColor);
    if (mouse.hover(this->_bg)) {
        this->scaleUp(0.02);
        this->_bg.setFillColor(sf::Color(colorRed, colorGreen, colorBlue));
        if (mouse.pressed() && this->_function)
            this->_function(nullptr);
    } else {
        this->scaleDown(0.02);
    }
}
