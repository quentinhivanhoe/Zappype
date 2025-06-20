/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** TrantorButtons functions
*/

#include "../includes/TrantorButtons.hpp"

Zappy::TrantorButtons::TrantorButtons(GUI *gui, std::shared_ptr<Trantorian> trantorian)
{
    this->_gui = gui;
    this->_targetTrantorian = trantorian;
    if (!this->_gui || !this->_targetTrantorian)
        throw Error("Missing gui or trantorian", "Trantor Buttons init");
    this->getFontComponent().loadFromFile("assets/arial.ttf");
    this->getBgComponent().setFillColor(sf::Color::White);
    this->getBgComponent().setOutlineColor(sf::Color::Black);
    this->getBgComponent().setOutlineThickness(1);
    this->getBgComponent().setSize(this->getSize());
    this->getBgComponent().setPosition(this->getPosition());
    this->getBgComponent().setOrigin({this->getPosition().x / 2, this->getPosition().y / 2});
    this->getTitleComponent().setFont(this->getFontComponent());
    this->getTitleComponent().setPosition(this->getPosition() + this->getTitlePositionOffset());
    this->getTitleComponent().setString("default");
    this->getTitleComponent().setCharacterSize(this->getCharacterSize());
    this->getTitleComponent().setLetterSpacing(2);
    this->getTitleComponent().setFillColor(sf::Color::Red);
    this->getTitleComponent().setOutlineThickness(0.5);
}

void Zappy::TrantorButtons::update(MouseStatus mouse)
{
    float colorRed = this->getFillColor().r + 50 - 150 * mouse.hold();
    float colorGreen = this->getFillColor().g + 50 - 150 * mouse.hold();
    float colorBlue = this->getFillColor().b + 50 - 150 * mouse.hold();
    Math::Clamp::function(&colorRed, 0, 255);
    Math::Clamp::function(&colorGreen, 0, 255);
    Math::Clamp::function(&colorBlue, 0, 255);
    this->getBgComponent().setFillColor(this->getFillColor());
    if (mouse.hover(this->getBgComponent())) {
        this->scaleUp(0.02);
        this->getBgComponent().setFillColor(sf::Color(colorRed, colorGreen, colorBlue));
        if (mouse.pressed() && this->_targetTrantorian && this->_gui->getTrantorianInfo())
            this->_gui->getTrantorianInfo()->setTrantorian(this->_targetTrantorian);
    } else {
        this->scaleDown(0.02);
    }
}