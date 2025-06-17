/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description: 
** GUI
*/
#include "../includes/GUI.hpp"

Zappy::GUI::GUI(const std::string &ip, size_t port)
{
    (void)ip;
    (void)port;
    // this->_networkInfo = std::make_shared<Network>(this);
    // this->_networkInfo->establishConnection(ip, port);
    // this->_networkInfo->initProcess();
    this->_window.create(sf::VideoMode(1920, 1080, 8), "Zappy GUI", sf::Style::Close);
    this->tile.getSprite().setScale(this->getTileScale(), this->getTileScale());
    this->tile.getSprite().setScale(this->getTileScale(), this->getTileScale());
    this->_map = Map(Vector2D(7.0, 4.0));
    this->sky.getSprite().setPosition(0, 0);
    this->init();
    this->run();
}

Zappy::GUI::~GUI()
{
}

void Zappy::GUI::init()
{
    initPaths();
    for (int i = 0; i < 8; i++) {
        this->_items.push_back(std::make_shared<Items>(this->spritePaths[i], i));
    }
    std::cout << "TEAMNAME" << this->_map.getTeams().size() << std::endl;
}

void Zappy::GUI::initPaths()
{
    this->spritePaths.push_back("../GUI/assets/egg_filled.png");
    this->spritePaths.push_back("../GUI/assets/food_filled.png");
    this->spritePaths.push_back("../GUI/assets/cristal_filled.png");
    this->spritePaths.push_back("../GUI/assets/cristal_filled.png");
    this->spritePaths.push_back("../GUI/assets/cristal_filled.png");
    this->spritePaths.push_back("../GUI/assets/cristal_filled.png");
    this->spritePaths.push_back("../GUI/assets/cristal_filled.png");
    this->spritePaths.push_back("../GUI/assets/cristal_filled.png");
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
        this->display_objects();
        this->display_trantor();
        this->_window.display();
    }   
}

void Zappy::GUI::display_map()
{
    Vector2D offset = Vector2D(1920/2, 0);
    for (size_t j = 0; j < this->getMap().getSize().getY(); j++){
        for (int i = 0; i < this->getMap().getSize().getX(); i++){
            offset.setX(offset.getX() - tile.getTexture().getSize().x  * this->getTileScale() / (2));
            offset.setY(offset.getY() + tile.getTexture().getSize().y  * this->getTileScale() / (2) - 18);
            this->tile.getSprite().setPosition(offset.getX(), offset.getY());
            this->_window.draw(this->tile.getSprite());
            _map.getTiles()[j][i].get()->setCenter(Vector2D(offset.getX() + (tile.getTexture().getSize().x * this->getTileScale() / 2), offset.getY() + (tile.getTexture().getSize().y * this->getTileScale() / 2)));
            _map.getTiles()[j][i].get()->setPos(offset);
            // std::cout << "tile pos : " << offset.getX() << " and " << offset.getY() << " / " << _map.getTiles()[j][i].get()->getPos().getX() << " and " << _map.getTiles()[j][i].get()->getPos().getY() << " center " <<  _map.getTiles()[j][i].get()->getCenter().getX() << " "<< _map.getTiles()[j][i].get()->getCenter().getY() << std::endl;
        }
        offset = Vector2D(
        (1920/2 + (tile.getTexture().getSize().x * this->getTileScale() / 2) * (j + 1)),
        (0 + (tile.getTexture().getSize().y * this->getTileScale() / 2 - 18) * (j + 1)));
    }
}

void Zappy::GUI::display_sky()
{
    this->_window.draw(this->sky.getSprite());
}

void Zappy::GUI::display_objects()
{
    for (size_t i = 0; i < this->_map.getTiles().size(); i++){
        for (size_t j = 0; j < this->_map.getTiles()[i].size(); j++){
            for (size_t k = 0; k < 8; k++){
                if (this->_map.getTiles()[i][j].get()->getItems()[k] > 0){
                    this->_items[k]->getSprite()->getSprite().setPosition(this->_map.getTiles()[i][j].get()->getCenter().getX(), this->_map.getTiles()[i][j].get()->getCenter().getY());
                    this->_items[k]->getSprite()->getSprite().setScale(0.1, 0.1);
                    this->_window.draw(this->_items[k]->getSprite()->getSprite());
                }                
            }
        }
    }
}

void Zappy::GUI::display_trantor()
{
    //printf("TEAM\n");
    for (size_t i = 0; i < this->_map.getTeams().size(); i++) {
        printf("I : %ld\n", i);   
        for (size_t j = 0; j < this->_map.getTeams()[i].get()->getTrantorian().size(); j++) {
            printf("J : %ld\n", j);   
            this->_map.getTeams()[i].get()->getTrantorian()[j].get()->getSprite()->getSprite().setPosition(50, 50);
            this->_map.getTeams()[i].get()->getTrantorian()[j].get()->getSprite()->getSprite().setScale(0.1, 0.1);
            this->_window.draw(this->_map.getTeams()[i].get()->getTrantorian()[j].get()->getSprite()->getSprite());
        }
    }
}