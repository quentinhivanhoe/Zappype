/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description: 
** GUI
*/
#include "../includes/GUI.hpp"
#include "../includes/TrantorButtons.hpp"
#include "../includes/TileInfo.hpp"

Zappy::GUI::GUI(const std::string &ip, size_t port)
{
    std::cout << "---------------SERVER---------------" << std::endl;
    this->_networkInfo = std::make_shared<Network>(this);
    this->_networkInfo->establishConnection(ip, port);
    this->_networkInfo->initProcess();
    std::srand(std::time(0));
    this->_recieveThread = std::thread(&Network::recieveFromServer, this->_networkInfo);
    this->_window.create(sf::VideoMode(1920, 1080, 8), "Zappy GUI", sf::Style::Close);
    this->tile.getSprite().setScale(this->getTileScale(), this->getTileScale());
    this->tile.getSprite().setScale(this->getTileScale(), this->getTileScale());
    for (size_t i = 0; i < this->_map->getTiles().size(); i++){
        for (size_t j = 0; j < this->_map->getTiles()[i].size(); j++){
            this->tile.set_offsets();
            this->_map->getTiles()[i][j].get()->setOffsetsList(this->tile.get_offsets());
        }
    }
    
    this->sky.getSprite().setPosition(0, 0);
    this->init();
    this->run();
    this->_recieveThread.join();
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
    this->_tileInfo = std::make_shared<TileInfo>(this);
    this->_trantorianInfo = std::make_shared<TrantorianInfo>(this);
    this->_view = sf::View(sf::FloatRect(0, 0, this->_window.getSize().x, this->_window.getSize().y));
    this->_window.setView(this->_view);
}

void Zappy::GUI::initPaths()
{
    this->spritePaths.push_back("../GUI/assets/egg_filled.png");
    this->spritePaths.push_back("../GUI/assets/food_filled.png");
    this->spritePaths.push_back("../GUI/assets/Gray_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Green_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Red_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Yellow_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Blue_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Orange_Cristal.png");
    std::cout << "init path done" << std::endl;
}

void Zappy::GUI::handleWindowEvents(  )
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            this->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            this->_tileInfo->setTile(nullptr);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            this->_tileInfo->setTile(this->_map->getTiles()[1][1]);
            this->_tileInfo->updateTrantorButtonsTab();
        }
    }
}

void Zappy::GUI::run()
{
    // this->_view.zoom(2);
    while (this->_window.isOpen()) {
        if (this->_framerateClock.getElapsedTime().asMicroseconds() < 1000000 / 60)
            continue;
        this->_framerateClock.restart();
        this->_mouse.update(this->_window);
        this->_tileInfo->update(this->_mouse);
        this->_trantorianInfo->update(this->_mouse);
        this->handleWindowEvents();
        this->_window.clear(sf::Color::Black);
        this->display_sky();
        this->display_map();
        this->display_objects();
        this->display_trantor();
        this->_trantorianInfo->render(this->_window);
        this->_tileInfo->render(this->_window);
        this->_window.setView(this->_view);
        this->_window.display();
    }
    this->_networkInfo->shutDown();
}

void Zappy::GUI::display_map()
{
    Vector2D offset = Vector2D(1920/2, 0);
    for (size_t j = 0; j < this->getMap()->getSize().getY(); j++){
        for (int i = 0; i < this->getMap()->getSize().getX(); i++){
            offset.setX(offset.getX() - tile.getTexture().getSize().x  * this->getTileScale() / (2) + 13);
            offset.setY(offset.getY() + tile.getTexture().getSize().y  * this->getTileScale() / (2) - 40);
            this->tile.getSprite().setPosition(offset.getX(), offset.getY());
            this->_window.draw(this->tile.getSprite());
            _map->getTiles()[j][i].get()->setCenter(Vector2D(offset.getX() + (tile.getTexture().getSize().x * this->getTileScale() / 2), offset.getY() + (tile.getTexture().getSize().y * this->getTileScale() / 2)));
            _map->getTiles()[j][i].get()->setPos(offset);
            // std::cout << "tile pos : " << offset.getX() << " and " << offset.getY() << " / " << _map->getTiles()[j][i].get()->getPos().getX() << " and " << _map->getTiles()[j][i].get()->getPos().getY() << " center " <<  _map->getTiles()[j][i].get()->getCenter().getX() << " "<< _map->getTiles()[j][i].get()->getCenter().getY() << std::endl;
        }
        offset = Vector2D(
        (1920/2 + (tile.getTexture().getSize().x * this->getTileScale() / 2 - 13) * (j + 1)),
        (0 + (tile.getTexture().getSize().y * this->getTileScale() / 2 - 40) * (j + 1)));
    }
}

void Zappy::GUI::display_sky()
{
    this->_window.draw(this->sky.getSprite());
}

void Zappy::GUI::display_objects()
{
    for (size_t i = 0; i < this->_map->getTiles().size(); i++){
        for (size_t j = 0; j < this->_map->getTiles()[i].size(); j++){
            for (size_t k = 0; k < 8; k++){
                if (this->_map->getTiles()[i][j].get()->getItems()[k] > 0){
                    this->_items[k]->getSprite()->getSprite().setPosition(this->_map->getTiles()[i][j].get()->getCenter().getX() + this->_map->getTiles()[i][j].get()->getOffsetsList()[k].getX(), 
                    this->_map->getTiles()[i][j].get()->getCenter().getY() + this->_map->getTiles()[i][j].get()->getOffsetsList()[k].getY());
                    this->_window.draw(this->_items[k]->getSprite()->getSprite());
                }                
            }
        }
    }
}

void Zappy::GUI::display_trantor()
{
    //printf("TEAM\n");
    for (auto team: this->_map->getTeams()) {
        for (auto trantorian: team.second->getTrantorians()) {
            trantorian->getSprite()->getSprite().setPosition(50, 50);
            trantorian->getSprite()->getSprite().setScale(0.1, 0.1);
            this->_window.draw(trantorian->getSprite()->getSprite());
        }
    }
}