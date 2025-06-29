/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile info functions
*/

#include "../includes/TileInfo.hpp"

Zappy::TileInfo::TileInfo(GUI *gui)
{
    if (!gui)
        throw Error("Missing gui", "TileInfo init");
    this->_gui = gui;
    this->_titleBarBg.setSize({320, 50});
    this->_titleBarBg.setFillColor(sf::Color::White);
    this->_titleBarBg.setOutlineColor(sf::Color::Black);
    this->_titleBarBg.setOutlineThickness(1);
    this->_titleBarBg.setPosition({0, 10});
    this->_bg.setSize({320, 300});
    this->_bg.setFillColor(sf::Color(240, 240, 240));
    this->_bg.setOutlineColor(sf::Color::Black);
    this->_bg.setOutlineThickness(1);
    this->_bg.setPosition({0, 60});
    this->_playerTitleBg.setSize({320, 50});
    this->_playerTitleBg.setFillColor(sf::Color::White);
    this->_playerTitleBg.setOutlineColor(sf::Color::Black);
    this->_playerTitleBg.setOutlineThickness(1);
    this->_playerTitleBg.setPosition({0, 360});
    this->_playerBg.setSize({320, 600});
    this->_playerBg.setFillColor(sf::Color(240, 240, 240));
    this->_playerBg.setOutlineColor(sf::Color::Black);
    this->_playerBg.setOutlineThickness(1);
    this->_playerBg.setPosition({0, 410});
    this->_font.loadFromFile("assets/arial.ttf");
    this->_text.setFont(this->_font);
    this->_selectedPos = sf::Vector2f(10, 0);
    this->_unselectedPos = sf::Vector2f(-400, 0);
    this->_tile = nullptr;
    this->_pos = this->_unselectedPos;
}

void Zappy::TileInfo::manageHiding()
{
    if (this->_gui->getTrantorianInfo()->isHiding())
        return;
    if (this->_pos.x <= this->_unselectedPos.x) {
        this->_pos.x = this->_unselectedPos.x;
        this->_tile = this->_nextTile;
        this->updateTrantorButtonsTab();
        this->_gui->getTrantorianInfo()->hide();
        this->_nextTile = nullptr;
        this->_hiding = false;
        return;
    }
    this->_pos.x -= this->_animationSpeed;
}

void Zappy::TileInfo::update(Zappy::MouseStatus mouse)
{
    if (this->_hiding)
        this->manageHiding();
    if (this->_tile && !this->_hiding) {
        this->_pos.x += this->_animationSpeed;
        Math::Clamp::function(this->_pos.x, this->_unselectedPos.x, this->_selectedPos.x);
    }
    for (auto button : this->_buttons) {
        button->update(mouse);
        button->setPosition(button->getBasePosition() + this->_pos);
    }
    this->_bg.setPosition(this->_pos + sf::Vector2f(0, 60));
    this->_playerBg.setPosition(this->_pos + sf::Vector2f(0, 410));
    this->_titleBarBg.setPosition(this->_pos + sf::Vector2f(0, 10));
    this->_playerTitleBg.setPosition(this->_pos + sf::Vector2f(0, 360));
    this->_growingNb += 0.05;
    this->_pos.y = 5 * std::sin(this->_growingNb);
}

void Zappy::TileInfo::render(sf::RenderWindow &window)
{
    window.draw(this->_bg);
    window.draw(this->_playerBg);
    window.draw(this->_titleBarBg);
    window.draw(this->_playerTitleBg);
    if (!this->_tile)
        return;
    this->drawText("TILE " + std::to_string(this->_tile->getIndex().x) + "-" + std::to_string(this->_tile->getIndex().y), this->_pos + sf::Vector2f(60, 20), sf::Color::Black, 30, window);
    this->drawText("Food: " + std::to_string(this->_tile->getNItem(Zappy::Item::FOOD)), this->_pos + sf::Vector2f(10, 70), sf::Color::Black, 30, window);
    this->drawText("Linemate: " + std::to_string(this->_tile->getNItem(Zappy::Item::LINEMATE)), this->_pos + sf::Vector2f(10, 110), sf::Color::Black, 30, window);
    this->drawText("Deraumere: " + std::to_string(this->_tile->getNItem(Zappy::Item::DERAUMERE)), this->_pos + sf::Vector2f(10, 150), sf::Color::Black, 30, window);
    this->drawText("Sibur: " + std::to_string(this->_tile->getNItem(Zappy::Item::SIBUR)), this->_pos + sf::Vector2f(10, 190), sf::Color::Black, 30, window);
    this->drawText("Mendiane: " + std::to_string(this->_tile->getNItem(Zappy::Item::MENDIANE)), this->_pos + sf::Vector2f(10, 230), sf::Color::Black, 30, window);
    this->drawText("Phiras: " + std::to_string(this->_tile->getNItem(Zappy::Item::PHIRAS)), this->_pos + sf::Vector2f(10, 270), sf::Color::Black, 30, window);
    this->drawText("Thystane: " + std::to_string(this->_tile->getNItem(Zappy::Item::THYSTAME)), this->_pos + sf::Vector2f(10, 310), sf::Color::Black, 30, window);
    this->drawText("TRANTORIANS ", this->_pos + sf::Vector2f(40, 365), sf::Color::Black, 30, window);
    for (auto button: this->_buttons)
        button->render(window);
}

void Zappy::TileInfo::updateTrantorButtonsTab()
{
    if (!this->_tile)
        return;
    this->_buttons.clear();
    size_t index = 0;

    for (auto trantorian: this->_gui->getMap()->getAllTrantorians()) {
        if (!trantorian.second)
            continue;
        if (trantorian.second->getTilePos().x != this->_tile->getIndex().x)
            continue;
        if (trantorian.second->getTilePos().y != this->_tile->getIndex().y)
            continue;
        std::shared_ptr<TrantorButtons> button = std::make_shared<TrantorButtons>(this->_gui, trantorian.second);
        button->setSize(sf::Vector2f(280, 80));
        button->setBgFillColor(sf::Color(230, 230, 230));
        button->setTextFillColor(sf::Color::Black);
        button->setTextOutlineColor(sf::Color::Black);
        button->setMaxScale(sf::Vector2f(1.05, 1.05));
        button->setMinScale(sf::Vector2f(0.95, 0.95));
        button->setTitle("Trantorian #" + std::to_string(trantorian.second->getID()));
        button->setPosition({160, static_cast<float>(500 + 100 * index)});
        button->setBasePosition({160, static_cast<float>(500 + 100 * index)});
        this->_buttons.push_back(button);
        index++;
    }
}

void Zappy::TileInfo::setTile(std::shared_ptr<Tile> tile)
{
    this->_hiding = true;
    this->_nextTile = tile;
    this->_gui->getTrantorianInfo()->setTrantorian(nullptr);
}

void Zappy::TileInfo::drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window)
{
    this->_text.setString(string);
    this->_text.setPosition(position);
    this->_text.setFillColor(color);
    this->_text.setCharacterSize(characterSize);
    window.draw(this->_text);
}
