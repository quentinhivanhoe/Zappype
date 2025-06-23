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
    this->_bg.setSize({320, 950});
    this->_bg.setFillColor(sf::Color(240, 240, 240));
    this->_bg.setOutlineColor(sf::Color::Black);
    this->_bg.setOutlineThickness(1);
    this->_bg.setPosition({320, 60});
    this->_titleBarBg.setSize({320, 50});
    this->_titleBarBg.setFillColor(sf::Color::White);
    this->_titleBarBg.setOutlineColor(sf::Color::Black);
    this->_titleBarBg.setOutlineThickness(1);
    this->_titleBarBg.setPosition({320, 10});
    this->_font.loadFromFile("assets/arial.ttf");
    this->_text.setFont(this->_font);
    this->_selectedPos = sf::Vector2f(10, 0);
    this->_unselectedPos = sf::Vector2f(-270, 0);
}

void Zappy::TrantorianInfo::manageHiding()
{
    if (this->_pos.x <= this->_unselectedPos.x) {
        this->_pos.x = this->_unselectedPos.x;
        this->_trantorian = this->_nextTrantorian;
        this->_nextTrantorian = nullptr;
        this->_hiding = false;
        return;
    }
    this->_pos.x -= this->_gui->getTileInfo()->getAnimationSpeed();
}

void Zappy::TrantorianInfo::update(Zappy::MouseStatus mouse)
{
    if (this->_hiding)
        this->manageHiding();
    this->_anchorPos = this->_gui->getTileInfo()->getPos();
    this->_bg.setPosition(this->_pos + this->_anchorPos + sf::Vector2f(320, 60));
    this->_titleBarBg.setPosition(this->_pos + this->_anchorPos + sf::Vector2f(320, 10));
    if (!this->_hiding && this->_trantorian)
        this->_pos.x += this->_gui->getTileInfo()->getAnimationSpeed();
    Math::Clamp::function(this->_pos.x, this->_unselectedPos.x, this->_selectedPos.x);
    (void)mouse;
}

void Zappy::TrantorianInfo::render(sf::RenderWindow &window)
{
    if (!this->_trantorian)
        return;
    window.draw(this->_bg);
    window.draw(this->_titleBarBg);
    this->drawText("TRANTORIAN #" + std::to_string(this->_trantorian->getID()), this->_anchorPos + this->_pos + sf::Vector2f(360, 20), sf::Color::Black, 30, window);
    this->drawText("Team: " + this->_trantorian->getTeamName(), this->_anchorPos + this->_pos + sf::Vector2f(330, 70), sf::Color::Black, 30, window);
    this->drawText("Level: " + std::to_string(this->_trantorian->getLevel()), this->_anchorPos + this->_pos + sf::Vector2f(330, 110), sf::Color::Black, 30, window);
    this->drawText("State: idling", this->_anchorPos + this->_pos + sf::Vector2f(330, 150), sf::Color::Black, 30, window);
    this->drawText("Position: " + std::to_string(this->_trantorian->getTilePos().x) + " - " + std::to_string(this->_trantorian->getTilePos().y), this->_anchorPos + this->_pos + sf::Vector2f(330, 190), sf::Color::Black, 30, window);
    this->drawText("Direction: " + std::to_string(this->_trantorian->getDirection()), this->_anchorPos + this->_pos + sf::Vector2f(330, 230), sf::Color::Black, 30, window);
    this->drawText("Inventory: ", this->_anchorPos + this->_pos + sf::Vector2f(330, 270), sf::Color::Black, 30, window);
    this->drawText("Food: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::FOOD)), this->_anchorPos + this->_pos + sf::Vector2f(360, 310), sf::Color::Black, 30, window);
    this->drawText("Linemate: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::LINEMATE)), this->_anchorPos + this->_pos + sf::Vector2f(360, 350), sf::Color::Black, 30, window);
    this->drawText("Deraumere: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::DERAUMERE)), this->_anchorPos + this->_pos + sf::Vector2f(360, 390), sf::Color::Black, 30, window);
    this->drawText("Sibur: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::SIBUR)), this->_anchorPos + this->_pos + sf::Vector2f(360, 430), sf::Color::Black, 30, window);
    this->drawText("Mendiane: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::MENDIANE)), this->_anchorPos + this->_pos + sf::Vector2f(360, 470), sf::Color::Black, 30, window);
    this->drawText("Phiras: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::PHIRAS)), this->_anchorPos + this->_pos + sf::Vector2f(360, 510), sf::Color::Black, 30, window);
    this->drawText("Thystane: " + std::to_string(this->_trantorian->getInventory()->getNItem(Zappy::Item::THYSTAME)), this->_anchorPos + this->_pos + sf::Vector2f(360, 550), sf::Color::Black, 30, window);
}

void Zappy::TrantorianInfo::drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window)
{
    this->_text.setString(string);
    this->_text.setPosition(position);
    this->_text.setFillColor(color);
    this->_text.setCharacterSize(characterSize);
    window.draw(this->_text);
}

void Zappy::TrantorianInfo::setTrantorian(std::shared_ptr<Zappy::Trantorian> trantorian)
{
    this->_nextTrantorian = trantorian;
    this->_hiding = true;
}