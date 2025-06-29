/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** TileButtons functions
*/

#include "../includes/TileButtons.hpp"

Zappy::TileButtons::TileButtons(GUI *gui, std::shared_ptr<Tile> tile)
{
    this->_gui = gui;
    this->_targetTile = tile;
    if (!this->_gui || !this->_targetTile)
        throw Error("Missing gui or tile", "Tile Buttons init");
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

void Zappy::TileButtons::update(MouseStatus mouse)
{
    float colorRed = this->getFillColor().r + 50 - 150 * mouse.hold();
    float colorGreen = this->getFillColor().g + 50 - 150 * mouse.hold();
    float colorBlue = this->getFillColor().b + 50 - 150 * mouse.hold();
    Math::Clamp::function(colorRed, 0, 255);
    Math::Clamp::function(colorGreen, 0, 255);
    Math::Clamp::function(colorBlue, 0, 255);
    this->getBgComponent().setFillColor(this->getFillColor());
    if (mouse.hover(this->getBgComponent())) {
        this->scaleUp(0.02);
        this->getBgComponent().setFillColor(sf::Color(colorRed, colorGreen, colorBlue));
        if (mouse.pressed() && this->_targetTile && this->_gui->getTileInfo())
            this->_gui->getTileInfo()->setTile(this->_targetTile);
    } else {
        this->scaleDown(0.02);
    }
}